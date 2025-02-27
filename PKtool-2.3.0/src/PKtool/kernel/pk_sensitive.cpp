/***********************************************************************

Copyright (C) 2004 - 2015 by Giovanni B. Vece

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

************************************************************************/

/***********************************************************************


 Original Author: Giovanni B. Vece

 Affiliation: Università Politecnica delle Marche (Italy)


************************************************************************/

#include "PKtool/kernel/pk_settings.h"
#ifdef PK_SYSC_22   
 #include "sysc/kernel/sc_process_handle.h"
#endif
#include "PKtool/kernel/pk_sensitive.h"

namespace pk_core  
{


#undef PK_OPERATOR_IMPL_1     
#undef PK_OPERATOR_IMPL_2
#undef PK_OPERATOR_IMPL_3


#define PK_OPERATOR_IMPL_1( sens_obj )                 \
        if(enabled) p_obj->operator << ( sens_obj );   \
		return *this;



#define PK_OPERATOR_IMPL_2( sens_obj )               \
        if(enabled) p_obj->operator () ( sens_obj ); \
		return *this;

#define PK_OPERATOR_IMPL_3( sens_obj )                           \
        if(enabled) p_obj->operator () ( handle_ , sens_obj );   \
        return *this;




// ----------------------------------------------------------------------------
//  CLASS : pk_sensitive
// ----------------------------------------------------------------------------


#ifdef PK_SYSC_22   

pk_sensitive& 
pk_sensitive::operator << ( sc_core::sc_process_handle handle_ )
{  PK_OPERATOR_IMPL_1(handle_)   };

  #if 0

    pk_sensitive& 
	pk_sensitive::operator << ( sc_method_handle handle_)
	{  PK_OPERATOR_IMPL_1(handle_)  }

    pk_sensitive& 
	pk_sensitive::operator << ( sc_thread_handle handle_ )
	{  PK_OPERATOR_IMPL_1(handle_)  }

  #endif // 0

#else

pk_sensitive&
pk_sensitive::operator << ( sc_method_handle handle_ )
{  PK_OPERATOR_IMPL_1(handle_)  }

pk_sensitive&
pk_sensitive::operator << ( sc_thread_handle handle_ )
{  PK_OPERATOR_IMPL_1( handle_ )  }

#endif

pk_sensitive&
pk_sensitive::operator () ( const sc_core::sc_event& event_ )
{  PK_OPERATOR_IMPL_2( event_ )  }

pk_sensitive&
pk_sensitive::operator () ( const sc_core::sc_interface& interface_ )
{  PK_OPERATOR_IMPL_2( interface_ )  }

pk_sensitive&
pk_sensitive::operator () ( const sc_core::sc_port_base& port_ )
{  PK_OPERATOR_IMPL_2( port_ )  };

pk_sensitive&
pk_sensitive::operator () ( sc_core::sc_event_finder& event_finder_ )
{  PK_OPERATOR_IMPL_2( event_finder_ )  };

pk_sensitive&
pk_sensitive::operator << ( const sc_core::sc_event& event_ )
{  PK_OPERATOR_IMPL_1( event_ )  }

pk_sensitive&
pk_sensitive::operator << ( const sc_core::sc_interface& interface_ )
{  PK_OPERATOR_IMPL_1( interface_ )  }

pk_sensitive&
pk_sensitive::operator << ( const sc_core::sc_port_base& port_ )
{  PK_OPERATOR_IMPL_1( port_ )  }

pk_sensitive&
pk_sensitive::operator << ( sc_core::sc_event_finder& event_finder_ )
{  PK_OPERATOR_IMPL_1( event_finder_ )  }

pk_sensitive&              
pk_sensitive::operator () ( sc_core::sc_cthread_handle handle_, 
						    sc_core::sc_event_finder& event_finder_ )
{  PK_OPERATOR_IMPL_3( event_finder_ )  }

pk_sensitive&
pk_sensitive::operator () ( sc_core::sc_cthread_handle handle_,
			                const in_if_b_type& interface_ )
{  PK_OPERATOR_IMPL_3( interface_ )  }

pk_sensitive&
pk_sensitive::operator () ( sc_core::sc_cthread_handle handle_,
			                const in_if_l_type& interface_ )
{  PK_OPERATOR_IMPL_3( interface_ )  }

pk_sensitive&
pk_sensitive::operator () ( sc_core::sc_cthread_handle handle_,
			                const in_port_b_type& port_ )
{  PK_OPERATOR_IMPL_3( port_ )  }

pk_sensitive&
pk_sensitive::operator () ( sc_core::sc_cthread_handle handle_,
			                const in_port_l_type& port_ )
{  PK_OPERATOR_IMPL_3( port_ )  }

pk_sensitive&
pk_sensitive::operator () ( sc_core::sc_cthread_handle handle_,
			                const inout_port_b_type& port_ )
{  PK_OPERATOR_IMPL_3( port_ )  }

pk_sensitive&
pk_sensitive::operator () ( sc_core::sc_cthread_handle handle_,
			                const inout_port_l_type& port_ )
{  PK_OPERATOR_IMPL_3( port_ )  }



// ----------------------------------------------------------------------------
//  CLASS : pk_sensitive_pos
// ----------------------------------------------------------------------------

#ifdef PK_SYSC_22   

pk_sensitive_pos& 
pk_sensitive_pos::operator << ( sc_core::sc_process_handle handle_ )
{
  if(enabled) p_obj->operator << ( handle_ );
  return *this;
};

  #if 0

    pk_sensitive_pos& 
	pk_sensitive_pos::operator << ( sc_method_handle )
	{
     if(enabled) p_obj->operator << ( handle_ );
     return *this;
    }

    pk_sensitive_pos& 
	pk_sensitive_pos::operator << ( sc_thread_handle )
	{
     if(enabled) p_obj->operator << ( handle_ );
     return *this;
    }

  #endif // 0

#else

pk_sensitive_pos&
pk_sensitive_pos::operator << ( sc_core::sc_method_handle handle_ )
{
    if(enabled) p_obj->operator << ( handle_ );
    return *this;
}

pk_sensitive_pos&
pk_sensitive_pos::operator << ( sc_core::sc_thread_handle handle_ )
{
    if(enabled) p_obj->operator << ( handle_ );
    return *this;
}

#endif

pk_sensitive_pos&
pk_sensitive_pos::operator () ( const in_if_b_type& interface_ )
{
 if(enabled) p_obj->operator () ( interface_ );
 return *this;
};

pk_sensitive_pos&
pk_sensitive_pos::operator () ( const in_if_l_type& interface_ )
{
 if(enabled) p_obj->operator () ( interface_ );
 return *this;
};

pk_sensitive_pos&
pk_sensitive_pos::operator () ( const in_port_b_type& port_ )
{
 if(enabled) p_obj->operator () ( port_ );
 return *this;
};

pk_sensitive_pos&
pk_sensitive_pos::operator () ( const in_port_l_type& port_ )
{
 if(enabled) p_obj->operator () ( port_ );
 return *this;
};

pk_sensitive_pos&
pk_sensitive_pos::operator () ( const inout_port_b_type& port_ )
{
 if(enabled) p_obj->operator () ( port_ );
 return *this;
};

pk_sensitive_pos&
pk_sensitive_pos::operator () ( const inout_port_l_type& port_ )
{
 if(enabled) p_obj->operator () ( port_ );
 return *this;
};

pk_sensitive_pos&
pk_sensitive_pos::operator << ( const in_if_b_type& interface_ )
{
	if(enabled) p_obj->operator << ( interface_ );   
    return *this;
}

pk_sensitive_pos&
pk_sensitive_pos::operator << ( const in_if_l_type& interface_ )
{
	if(enabled) p_obj->operator << ( interface_ );   
    return *this;
}

pk_sensitive_pos&
pk_sensitive_pos::operator << ( const in_port_b_type& port_ )
{
	if(enabled) p_obj->operator << ( port_ );   
    return *this;
}

pk_sensitive_pos&
pk_sensitive_pos::operator << ( const in_port_l_type& port_ )
{
   if(enabled) p_obj->operator << ( port_ );   
   return *this;
}

pk_sensitive_pos&
pk_sensitive_pos::operator << ( const inout_port_b_type& port_ )
{
   if(enabled) p_obj->operator << ( port_ );   
   return *this;
}

pk_sensitive_pos&
pk_sensitive_pos::operator << ( const inout_port_l_type& port_ )
{
	if(enabled) p_obj->operator << ( port_ );   
    return *this;
}


// ----------------------------------------------------------------------------
//  CLASS : pk_sensitive_neg
// ----------------------------------------------------------------------------


#ifdef PK_SYSC_22   

pk_sensitive_neg& 
pk_sensitive_neg::operator << ( sc_core::sc_process_handle handle_ )
{
  if(enabled) p_obj->operator << ( handle_ );
  return *this;
};

  #if 0

    pk_sensitive_neg& 
	pk_sensitive_neg::operator << ( sc_core::sc_method_handle )
	{
     if(enabled) p_obj->operator << ( handle_ );
     return *this;
    }

    pk_sensitive_neg& 
	pk_sensitive_neg::operator << ( sc_core::sc_thread_handle )
	{
     if(enabled) p_obj->operator << ( handle_ );
     return *this;
    }

  #endif // 0

#else

pk_sensitive_neg&
pk_sensitive_neg::operator << ( sc_core::sc_method_handle handle_ )
{
    if(enabled) p_obj->operator << ( handle_ );
    return *this;
}

pk_sensitive_neg&
pk_sensitive_neg::operator << ( sc_core::sc_thread_handle handle_ )
{
    if(enabled) p_obj->operator << ( handle_ );
    return *this;
}

#endif

pk_sensitive_neg&
pk_sensitive_neg::operator () ( const in_if_b_type& interface_ )
{
 if(enabled) p_obj->operator () ( interface_ );
 return *this;
};

pk_sensitive_neg&
pk_sensitive_neg::operator () ( const in_if_l_type& interface_ )
{
 if(enabled) p_obj->operator () ( interface_ );
 return *this;
};

pk_sensitive_neg&
pk_sensitive_neg::operator () ( const in_port_b_type& port_ )
{
 if(enabled) p_obj->operator () ( port_ );
 return *this;
};

pk_sensitive_neg&
pk_sensitive_neg::operator () ( const in_port_l_type& port_ )
{
 if(enabled) p_obj->operator () ( port_ );
 return *this;
};

pk_sensitive_neg&
pk_sensitive_neg::operator () ( const inout_port_b_type& port_ )
{
 if(enabled) p_obj->operator () ( port_ );
 return *this;
};

pk_sensitive_neg&
pk_sensitive_neg::operator () ( const inout_port_l_type& port_ )
{
 if(enabled) p_obj->operator () ( port_ );
 return *this;
};

pk_sensitive_neg&
pk_sensitive_neg::operator << ( const in_if_b_type& interface_ )
{
	if(enabled) p_obj->operator << ( interface_ );   
    return *this;
}

pk_sensitive_neg&
pk_sensitive_neg::operator << ( const in_if_l_type& interface_ )
{
	if(enabled) p_obj->operator << ( interface_ );   
    return *this;
}

pk_sensitive_neg&
pk_sensitive_neg::operator << ( const in_port_b_type& port_ )
{
	if(enabled) p_obj->operator << ( port_ );   
    return *this;
}

pk_sensitive_neg&
pk_sensitive_neg::operator << ( const in_port_l_type& port_ )
{  
	if(enabled) p_obj->operator << ( port_ );   
    return *this;
}

pk_sensitive_neg&
pk_sensitive_neg::operator << ( const inout_port_b_type& port_ )
{
	if(enabled) p_obj->operator << ( port_ );  
    return *this;
}

pk_sensitive_neg&
pk_sensitive_neg::operator << ( const inout_port_l_type& port_ )
{
	if(enabled) p_obj->operator << ( port_ );   
    return *this;
}



}  
