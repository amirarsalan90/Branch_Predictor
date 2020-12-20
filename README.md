# Branch_Predictor

This code is a branch predictor simulator, and can be used to design branch predictors suited to the SPECint95 benchmarks. The predictor includes Smith n-bit counter predictor, GShare predictor, and a Hybrid predictor. The simulator reads a trace file with the following format:<br/><br/>
**\<hex branch PC\> t|n** <br/><br/>
where <hex branch PC> is the address of branch instruction, "t" indicates the branch is actually taken, and "n" indicates the branch is actually not taken.<br/>
The command-line arguments that the simulator accepts is as follows:<br/><br/>
**sim smith \<N\> \<tracefile\>**: in which the program simulates an N-bit Smith branch predictor <br/>
**sim bimodal \<M\> \<tracefile\>**: in which M is the number of PC bits that is used to index the bimodal table <br/>
**sim gshare \<M\> \<N\> \<tracefile\>**: in which M is the number of PC bits and N is the global branch history register bits used to inddex the gshare table <br/>
**sim hybrid \<K\> \<M1\> \<N\> \<M2\> \<tracefile\>**: in which K is number of PC bits, M1 and N are the number of PC bits and global branch history register bits, and M2 is the number of PC bits used to index the bimodal table.
