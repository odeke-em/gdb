# This should match the output of gas -alc cond.s.

.*cond.s.*


   1[ 	]+.if	0
   8[ 	]+.else
   9[ 	]+.if	1
  10[ 	]+.endc
  11 0000 0[02]00 ?000[02][ 	]+.long[ 	]+2
  12[ 	]+.if	0
  14[ 	]+.else
  15 0004 0[04]00 ?000[04][ 	]+.long[ 	]+4
  16[ 	]+.endc
  17[ 	]+.endc
