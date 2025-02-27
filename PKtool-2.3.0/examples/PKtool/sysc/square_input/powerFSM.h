#ifndef POWERFSM_H
#define POWERFSM_H


 // power states

 enum power_st{standby_st, normal_st, overflow_st};


 int stb_cnt ;

 //powerFSM functions

 PK_STATE_FC(standby_st)
 {
  //static int cnt = 1;
  while(stb_cnt < 3)
  {
   ++stb_cnt;
   return standby_st;
  };
  if(standby == true) 
      return standby_st;
  else
  {
   stb_cnt = 1;
   if(input.read() >= over_value) return overflow_st; 
   return normal_st;
  }
 }; 
 
  
 PK_STATE_FC( normal_st )
 {
  if(standby == true) return standby_st;
  if(input.read() >= over_value) return overflow_st; 
  return normal_st;
 };  

 
  PK_STATE_FC(overflow_st)
  {
   if(standby == true) return standby_st;
   else if(input.read() >= over_value) return overflow_st;
   else return normal_st;
  };




#endif
