import re
import pandas as pd
import numpy as np
import plotly.express as px
import plotly.graph_objects as go
from plotly.subplots import make_subplots
from collections import defaultdict

def parse_log_to_dataframe(log_file):
    """Enhanced parser with error handling"""
    data = []
    with open(log_file, 'r') as f:
        for line in f:
            try:
                # Extract using more flexible regex
                match = re.search(
                    r"PE\((\d+),(\d+)\).*?from\s*\((\d+),(\d+)\).*?at\s*(\d+)\s*ns.*?LATENCY:\s*(\d+)",
                    line.strip(), re.IGNORECASE
                )
                if match:
                    dest_x, dest_y, src_x, src_y, time_ns, latency = map(int, match.groups())
                    data.append({
                        'src_x': src_x, 'src_y': src_y,
                        'dest_x': dest_x, 'dest_y': dest_y,
                        'time_ns': time_ns, 'latency_ns': latency,
                        'src': f"({src_x},{src_y})",
                        'dest': f"({dest_x},{dest_y})",
                        'path': f"({src_x},{src_y})→({dest_x},{dest_y})"
                    })
            except:
                continue
    
    df = pd.DataFrame(data)
    
    # Calculate derived metrics
    df['hops'] = abs(df['src_x'] - df['dest_x']) + abs(df['src_y'] - df['dest_y'])
    df['time_ms'] = df['time_ns'] / 1000  # Convert to microseconds
    
    return df

def create_interactive_dashboard(df):
    """Create a Plotly dashboard with tabs"""
    fig = make_subplots(
        rows=3, cols=2,
        specs=[[{"type": "histogram"}, {"type": "scatter"}],
               [{"type": "heatmap"}, {"type": "bar"}],
               [{"type": "scatter3d"}, {"type": "box"}]],
        subplot_titles=(
            "Latency Distribution", "Latency vs Hops",
            "Router Activity Heatmap", "Throughput Over Time",
            "3D Latency View", "Latency by Path"
        )
    )
    
    # 1. Latency Histogram
    fig.add_trace(
        go.Histogram(
            x=df['latency_ns'],
            nbinsx=20,
            name='Latency',
            marker_color='#636EFA'
        ),
        row=1, col=1
    )
    
    # 2. Latency vs Hops
    fig.add_trace(
        go.Scatter(
            x=df['hops'],
            y=df['latency_ns'],
            mode='markers',
            name='Packets',
            marker=dict(
                size=8,
                color=df['latency_ns'],
                colorscale='Viridis',
                showscale=True
            )
        ),
        row=1, col=2
    )
    
    # 3. Heatmap
    heatmap_data = df.groupby(['dest_x', 'dest_y']).size().unstack().fillna(0)
    fig.add_trace(
        go.Heatmap(
            z=heatmap_data.values,
            x=[0,1,2],
            y=[0,1,2],
            colorscale='YlOrRd',
            colorbar=dict(title='Packets')
        ),
        row=2, col=1
    )
    
    # 4. Throughput
    time_bins = pd.cut(df['time_ms'], bins=20)
    throughput = df.groupby(time_bins).size()
    fig.add_trace(
        go.Bar(
            x=throughput.index.astype(str),
            y=throughput.values,
            name='Throughput'
        ),
        row=2, col=2
    )
    
    # 5. 3D View
    fig.add_trace(
        go.Scatter3d(
            x=df['src_x'],
            y=df['src_y'],
            z=df['latency_ns'],
            mode='markers',
            marker=dict(
                size=5,
                color=df['latency_ns'],
                colorscale='Plasma',
                opacity=0.8
            ),
            text=df['path']
        ),
        row=3, col=1
    )
    
    # 6. Path Analysis
    top_paths = df['path'].value_counts().nlargest(10).index
    filtered_df = df[df['path'].isin(top_paths)]
    fig.add_trace(
        go.Box(
            x=filtered_df['path'],
            y=filtered_df['latency_ns'],
            name='Path Latency'
        ),
        row=3, col=2
    )
    
    # Update layout
    fig.update_layout(
        height=1200,
        width=1200,
        title_text="NoC Performance Dashboard",
        showlegend=False
    )
    
    # Axis labels
    fig.update_xaxes(title_text="Latency (ns)", row=1, col=1)
    fig.update_yaxes(title_text="Count", row=1, col=1)
    fig.update_xaxes(title_text="Hop Count", row=1, col=2)
    fig.update_yaxes(title_text="Latency (ns)", row=1, col=2)
    fig.update_xaxes(title_text="X Position", row=2, col=1)
    fig.update_yaxes(title_text="Y Position", row=2, col=1)
    fig.update_xaxes(title_text="Time Bins", row=2, col=2)
    fig.update_yaxes(title_text="Packets", row=2, col=2)
    fig.update_scenes(
        xaxis_title='Source X',
        yaxis_title='Source Y',
        zaxis_title='Latency (ns)',
        row=3, col=1
    )
    fig.update_xaxes(title_text="Path", row=3, col=2)
    fig.update_yaxes(title_text="Latency (ns)", row=3, col=2)
    
    return fig

def generate_path_analysis(df):
    """Generate detailed path statistics"""
    path_stats = df.groupby('path').agg({
        'latency_ns': ['count', 'mean', 'std', 'min', 'max'],
        'hops': 'first'
    }).sort_values(('latency_ns', 'mean'), ascending=False)
    
    print("\nTop 10 Longest Latency Paths:")
    print(path_stats.head(10).to_string())
    
    return path_stats

def main():
    # Load and parse data
    df = parse_log_to_dataframe('noc_log.txt')
    
    # Generate statistics
    print(f"\n📊 Basic Statistics:")
    print(f"Total packets: {len(df)}")
    print(f"Average latency: {df['latency_ns'].mean():.2f} ± {df['latency_ns'].std():.2f} ns")
    print(f"Median latency: {df['latency_ns'].median():.2f} ns")
    print(f"Min/Max latency: {df['latency_ns'].min()}/{df['latency_ns'].max()} ns")
    
    # Generate path analysis
    path_stats = generate_path_analysis(df)
    
    # Create interactive dashboard
    fig = create_interactive_dashboard(df)
    
    # Save outputs
    df.to_csv('noc_analysis.csv', index=False)
    path_stats.to_csv('path_statistics.csv')
    fig.write_html("noc_dashboard.html")
    
    print("\n✅ Analysis complete!")
    print("Saved outputs:")
    print("- noc_analysis.csv (raw data)")
    print("- path_statistics.csv (path metrics)")
    print("- noc_dashboard.html (interactive dashboard)")

if __name__ == "__main__":
    main()
