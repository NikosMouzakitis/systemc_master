import re
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.colors import LogNorm
from mpl_toolkits.mplot3d import Axes3D
import seaborn as sns
from io import StringIO

SIZE = 3


def parse_thermal_data(csv_file):
    """Generic parser for any mesh size"""
    with open(csv_file, 'r') as f:
        content = f.read()

    # Find all data blocks
    blocks = re.split(r'Time,Core_\d+_\d+(?:,Core_\d+_\d+)*\n', content)
    blocks = [b.strip() for b in blocks if b.strip()]

    # Find all core positions from header
    header = re.search(r'Time,(Core_\d+_\d+(?:,Core_\d+_\d+)*)\n', content).group(1)
    core_columns = header.split(',')
    
    # Process all data blocks
    data = []
    for block in blocks:
        for line in block.split('\n'):
            if line.strip():
                values = line.split(',')
                timestamp = float(values[0])
              #  temps = {core: float(temp) for core, temp in zip(core_columns, values[1:])}
                temps = {core: float(temp) if temp else None for core, temp in zip(core_columns, values[1:])}

                data.append({'Time': timestamp, **temps})

    return pd.DataFrame(data).sort_values('Time')

def visualize_thermal_data(df):
    """Generic visualization for any mesh size"""
    # Melt data for plotting
    melted = df.melt(id_vars=['Time'], var_name='Core', value_name='Temperature')
    
    # Create figure
    plt.figure(figsize=(14, 8))
    
    # Plot all cores
    sns.lineplot(data=melted, x='Time', y='Temperature', hue='Core',
                linewidth=1.5, alpha=0.8)
    
    # Formatting
    plt.title('NoC Routers Temperature Over Time', fontsize=16)
    plt.ylabel('Temperature (°C)', fontsize=14)
    plt.xlabel('Time (s)', fontsize=14)
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', title='router')
    
    # Critical temperature markers
    plt.axhline(y=70, color='red', linestyle='--', alpha=0.3, label='Critical (70°C)')
    plt.axhline(y=60, color='orange', linestyle='--', alpha=0.3, label='Warning (60°C)')
    
    plt.tight_layout()
    plt.show()

    # Additional heatmap visualization
    plt.figure(figsize=(12, 6))
    pivot_df = df.set_index('Time')
    sns.heatmap(pivot_df.T, cmap='coolwarm', center=60)
    plt.title('Temperature Heatmap Over Time')
    plt.ylabel('Router')
    plt.xlabel('Time (s)')
    plt.tight_layout()
    plt.show()



def parse_noc_log(log_file):
    """Parse NoC simulation log into structured data"""
    data = []
    with open(log_file, 'r') as f:
        for line in f:
            match = re.search(
                r"PE\((\d+),(\d+)\).*from \((\d+),(\d+)\).*at (\d+) ns.*LATENCY:\s+(\d+)",
                line.strip()
            )
            if match:
                dest_x, dest_y, src_x, src_y, time_ns, latency = map(int, match.groups())
                data.append({
                    'src_x': src_x,
                    'src_y': src_y,
                    'dest_x': dest_x,
                    'dest_y': dest_y,
                    'time_ns': time_ns,
                    'latency_ns': latency
                })
    return pd.DataFrame(data)

def analyze_data(df):
    """Calculate derived metrics"""
    # Calculate hop count (Manhattan distance)
    df['hops'] = abs(df['src_x'] - df['dest_x']) + abs(df['src_y'] - df['dest_y'])
    
    # Time binning for throughput analysis
    max_time = df['time_ns'].max()
    bin_size = max(20, max_time // 10)  # Adaptive bin size
    df['time_bin'] = pd.cut(df['time_ns'], bins=range(0, max_time + bin_size, bin_size))
    
    return df

def plot_latency_distribution(df):
    """Plot histogram of packet latencies"""
    plt.figure(figsize=(10, 6))
    plt.hist(df['latency_ns'], bins=20, edgecolor='k', alpha=0.7)
    plt.xlabel('Latency (ns)')
    plt.ylabel('Number of Packets')
    plt.title('Packet Latency Distribution')
    plt.grid(True, alpha=0.3)
    plt.show()

def plot_path_heatmap(df):
    """Plot router activity heatmap"""
    # Count packet arrivals per router
    router_counts = df.groupby(['dest_x', 'dest_y']).size().reset_index(name='counts')
    
    # Create 3x3 grid
    heatmap = np.zeros((SIZE, SIZE))
    for _, row in router_counts.iterrows():
        heatmap[row['dest_y'], row['dest_x']] = row['counts']
    
    plt.figure(figsize=(8, 6))
    plt.imshow(heatmap, cmap='YlOrRd', norm=LogNorm())
    plt.colorbar(label='Packet Count')
    
    # Annotate each cell
    for y in range(SIZE):
        for x in range(SIZE):
            plt.text(x, y, f'{heatmap[y, x]:.0f}', 
                    ha='center', va='center', color='black')
    
    plt.title('Router Activity Heatmap (Packet Destinations)')
    plt.xlabel('X Position')
    plt.ylabel('Y Position')
    plt.xticks([0, 1, 2])
    plt.yticks([0, 1, 2])
    plt.show()

def plot_throughput(df):
    """Plot throughput over time"""
    throughput = df.groupby('time_bin').size()
    
    plt.figure(figsize=(10, 6))
    throughput.plot(kind='bar', width=0.9, alpha=0.7)
    
    # Calculate and plot moving average
    window_size = 3
    ma = throughput.rolling(window=window_size, center=True).mean()
    plt.plot(range(len(throughput)), ma, color='red', 
             label=f'{window_size}-bin Moving Avg')
    
    plt.xlabel('Time Bins')
    plt.ylabel('Packets per Bin')
    plt.title('Network Throughput Over Time')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.xticks(rotation=45)
    plt.tight_layout()
    plt.show()

def plot_latency_vs_hops(df):
    """Scatter plot of latency vs hop count"""
    plt.figure(figsize=(10, 6))
    
    # Plot individual packets
    plt.scatter(df['hops'], df['latency_ns'], alpha=0.5, label='Individual Packets')
    
    # Plot average latency per hop count
    avg_latency = df.groupby('hops')['latency_ns'].mean()
    plt.plot(avg_latency.index, avg_latency.values, 'ro-', 
             markersize=10, linewidth=2, label='Average Latency')
    
    plt.xlabel('Number of Hops')
    plt.ylabel('Latency (ns)')
    plt.title('Latency vs Hop Count')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.xticks(range(1, 8))  # Max hops in 3x3 mesh is 4
    plt.show()

def plot_3d_latency(df):
    """Interactive 3D plot of latency by source and destination"""
    fig = plt.figure(figsize=(12, 8))
    ax = fig.add_subplot(111, projection='3d')
    
    # Create color mapping based on latency
    colors = plt.cm.viridis(df['latency_ns'] / df['latency_ns'].max())
    
    # Plot each packet
    sc = ax.scatter(
        df['src_x'], df['src_y'], df['latency_ns'],
        c=df['latency_ns'], cmap='viridis',
        s=50, alpha=0.7
    )
    
    ax.set_xlabel('Source X')
    ax.set_ylabel('Source Y')
    ax.set_zlabel('Latency (ns)')
    ax.set_title('Packet Latency by Source Coordinates')
    ax.set_xticks([0, 1, 2, 3, 4])
    ax.set_yticks([0, 1, 2, 3, 4])
    
    # Add colorbar
    cbar = plt.colorbar(sc, pad=0.1)
    cbar.set_label('Latency (ns)')
    
    plt.tight_layout()
    plt.show()


def main():
    # Step 1: Parse the log file
    log_file = 'noc_log.txt'  # Change to your log file path
    df = parse_noc_log(log_file)
    
    # Step 2: Analyze data
    df = analyze_data(df)
    
    print("\nBasic Statistics:")
    print(f"Total packets: {len(df)}")
    print(f"Average latency: {df['latency_ns'].mean():.2f} ns")
    print(f"Maximum latency: {df['latency_ns'].max()} ns")
    print(f"Minimum latency: {df['latency_ns'].min()} ns")
    
    # Step 3: Generate visualizations
    plot_latency_distribution(df)
    plot_path_heatmap(df)
    plot_throughput(df)
    plot_latency_vs_hops(df)


    thermal_df = parse_thermal_data('thermal_data.csv')
    print(f"Data loaded successfully for {len(thermal_df.columns)-1} cores")
    print(f"Time range: {thermal_df['Time'].min()} to {thermal_df['Time'].max()} seconds")
    visualize_thermal_data(thermal_df)

if __name__ == "__main__":
    main()
