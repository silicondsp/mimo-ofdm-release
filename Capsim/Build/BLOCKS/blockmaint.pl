
#!/usr/bin/perl
#
# Copyright (C) 1989-2017 Silicon DSP  Corporation
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2 of the License, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
#

#
#
# Script for adding blocks to database blockdatabase.dat and to generate krn_blocklib.c
#
#
# In MacPerl, save as droplet. Drag files or dirs onto the script.
# Requires the 'ssUtilities.pl' in the MacPerl lib folder to work.
# 
# File drag and drop  script by Sandra Silcot, Jan 1995, ssilcot@www.unimelb.edu.au
#
# Written by Sasan Ardalan, Dec.2, 1997
#
# Updated for C++ in this case QT by Sasan Ardalan October 20, 2017

#require 'ssUtilities.pl';



# print "\n$0\n$DateTime\nCapsim Block Maintenance!\n==============================================\n";


$listFlag=0;
$genFlag=0;
$flagTrue=0;
$flag="a";
foreach $f (@ARGV) {

#    if (-d $f) {
#        print "A directory: $f\n";
#        @fileList =&get_recursive_filelist ($f);

								
#        foreach $file (@fileList) {
#        $fileFlag=1;
#		&addDatabase;
    
#       }

#$flag = substr $f,1,1;



print "arg is:",$f,"FLAG is:",$flag,"\n";

if($flagTrue eq 1 && $flag eq "z" ) {
        print "111ADDING top Databae\n";
      #
        # Here we process an individual file
        #
        $file=$f;
        $f="";

        $fileFlag=1;
        if( $flag eq "a") {
               &addDatabase;
        }


}

if($flagTrue ==0)  {
	$flag=$f;
#     print "arg flag:",$flag,"\n";
   #  chop($flag);
#     print "arg chop:",$flag,"\n";
     if($flag eq "g") {
  #       print "arg have g flag:",$flag,"\n";
     }
}



if( $flagTrue == 0 && ($flag eq "a" ||  $flag eq "d" || $flag eq "l" || $flag eq "g")) {        
    
    print "Detected flag=",$flag,"\n";
    $flagTrue=1;
     
   } else {
	#
	# Here we process an individual file
	#
	$file=$f;
	$f="";
	
	$fileFlag=1;
	#print "ADDING top Databae\n";
	if( $flag eq "a") {
               &addDatabase;
        }


  }
}


if($flagTrue ==0  || $flag eq "a") {
	print "End of blockmaint script.\n\nDone!\n";

	exit;
}

			
if($fileFlag == 1) {
        	#print "block is: $file\n";
			$blockname="$f$file";
			# strip the .s at the end of the file
			$blockname =~ s/\.s//;
			@PATHS=split(/\\/,$blockname);
			$blockname=$PATHS[$#PATHS];
#                print "block name is: $file\n";
}


 $listFlag=0;
#$action = MacPerl::Pick("Select Action", "Add", "Delete", "List");

if($flag eq "l") {
#     print "Listing ... \n";
     $listFlag=1;
     &addDatabase;


} elsif ( $flag eq "d") {

#	$blockname=MacPerl::Ask("Enter block name to delete");
#        $blockname=$f;
        print "Deleting $blockname ...\n";
	&DeleteBlock;



} elsif ($flag eq "g") {
    $genFlag=1;
    &addDatabase;

}


#print "End of blockmaint script.\n\nDone!\n";






#
# Delete Database Block
#
sub DeleteBlock {


			$doit=0;

			open (INFILE, "blockdatabase.dat") || die "could not open infile $f";
#   			print "\nProcessing $f\n"; # print a message to the STDOUT default output window


    		
    		#
    		# Create the new blockdatabase.dat file
    		#
    		
 			open(dataBaseFile,">blockdatabase.dat.gen") || die("Unable to open  file to write\n");



    		$linenum = 0;
    		# now read each line - it will go into $_ / add <P> tag to all linebreaks
    		
    		$flag=0;
    		#   @BLOCKS=("");
    		@COMMENTS=("");
    		while (<INFILE>) {
    			
     							
       	  		
      							
       	  		if($_ =~ /\n/) {
       	  			@theWords=split(/ /,$_);
 
       	  			if($_ =~ /\*END/) {
 #    	  			    print "found end\n";
       	  			    $_="\n";
       	  				$flag=1;
       	  			}
       	  			if($flag ==1 && ($_ =~ /\*FUNCDECL/)) {
       	  			   $flag=2;
       	  			
       	  			}
 
					if($#theWords==2 && $flag ==0) {
							if($theWords[0] eq $blockname) {
								print "Found:";print $blockname; print "\n"; 
								$doit=1;
														
							} else {
							  
								push @BLOCKS,($theWords[0]);
							}
		
					}
					if($flag == 1) {
						push @COMMENTS,$_;
					
					
					}
				
		  		}  # we would say 'chop;' to get rid of it
        	  	$linenum++;  # increment our counter
   			}
    		# close it
    		close (INFILE);


			if($doit == 0) {
					return;
			}
			
			rename "blockdatabase.dat","blockdatabase_old.dat";

    		
    		@sortedBlocks=sort (@BLOCKS);
    		
    		
    		#
    		# Create the new blockdatabase.dat file
    		#
    		
 			open(dataBaseFile,">blockdatabase.dat") || die("Unable to open  file to write\n");
 			
 			print (dataBaseFile "! This is the core library data\n!\n");
 			
    		$kk=0;
    		foreach $block (@sortedBlocks) {
    		         print(dataBaseFile  $block," ");print(dataBaseFile  $block," "); print(dataBaseFile  substr($block,0,7),"\n");
    		             		
    		}   		
    		print(dataBaseFile  "*END\n\n");
    		
    		foreach $commline (@COMMENTS) {
    			print(dataBaseFile $commline);
    		
    		}    		
    		print(dataBaseFile  "*FUNCDECL\n\n");
    		print(dataBaseFile  "/* model table Definition */\n");
    		print(dataBaseFile  "*MODTABL\n*END\n");
    		
    		
			close(dataBaseFile); 

}



#
# add dropped blocks to database "blockdatabase.dat"
#
sub addDatabase {
		

print "In addDatabase $fileFlag is:",$fileFlag,"\n";	
			
if($fileFlag == 1) {
        	print "$file\n";
			$blockname="$f$file";
			# strip the .s at the end of the file
			$blockname =~ s/\.s//;
			@PATHS=split(/:/,$blockname);
			$blockname=$PATHS[$#PATHS];
}
		
#			print "The blockname  is ==> $blockname","\n";
		


			open (INFILE, "blockdatabase.dat") || die "could not open infile $f";
#   			print "\nProcessing $f\n"; # print a message to the STDOUT default output window

    		$linenum = 0;
    		# now read each line - it will go into $_ / add <P> tag to all linebreaks
    		
		#XXXXXXXXXXXXXXXXXXXXXX $flag=0;
    		#   @BLOCKS=("");
    		@COMMENTS=("");
    		while (<INFILE>) {
#             print $_;
    			
     							
       	  		if($_ =~ /\n/) {
       	  			@theWords=split(/ /,$_);
 
       	  			if($_ =~ /\*END/) {
       	 # 			    print "found end\n";
       	  			    $_="\n";
       	  				$flag=1;
       	  			}
       	  			if($flag ==1 && ($_ =~ /\*FUNCDECL/)) {
       	  			   $flag=2;
       	  			
       	  			}
 
					if($#theWords==2 && $flag ==0) {
							if($theWords[0] eq $blockname) {
								print "BLOCK ALREADY EXITS:";print $blockname; print "\n"; 
								return;							
							}

 #      print $theWords[0];print "\n";
							  
							push @BLOCKS,($theWords[0]);
		
					}
					if($flag == 1) {
						push @COMMENTS,$_;
					
					
					}
				
		  		}  # we would say 'chop;' to get rid of it
        	  	$linenum++;  # increment our counter
   			}
    		# close it
    		close (INFILE);
    		
    		if($listFlag ==1) {
    		    @sortedBlocks=sort (@BLOCKS);
    		    foreach $block (@sortedBlocks) {
    		    	print $block; print "\n";
    		    }
				return;
    		}   		
    		
			

    		
    		if($genFlag == 0) {
    		     rename "blockdatabase.dat","blockdatabase_old.dat";
    		     push  @BLOCKS, ($blockname);
    		
    		
    		     @sortedBlocks=sort (@BLOCKS);
    		
    		
    		    # Create the new blockdatabase.dat file
    		    #
    		
 			    open(dataBaseFile,">blockdatabase.dat") || die("Unable to open  file to write\n");
 			
 			    print (dataBaseFile "! This is the core library data\n!\n");
 			
    		    $kk=0;
    		    foreach $block (@sortedBlocks) {
    		         print(dataBaseFile  $block," ");print(dataBaseFile  $block," "); print(dataBaseFile  substr($block,0,7),"\n");
    		             		
    		    }   		
    		    print(dataBaseFile  "*END\n\n");
    		
    		    foreach $commline (@COMMENTS) {
    		 	     print(dataBaseFile $commline);
    		
    		    }    		
    		    print(dataBaseFile  "*FUNCDECL\n\n");
    		    print(dataBaseFile  "/* model table Definition */\n");
    		    print(dataBaseFile  "*MODTABL\n*END\n");
    		
    		
			    close(dataBaseFile);
			    print "Block Added:",$blockname,"\n";
			
			} else {
			    @sortedBlocks=sort (@BLOCKS);
			
			}
			
			#
			# Generate the C code for krn_blocklib.c
			#
    		open(CCODE,">krn_blocklib.c") || die("Unable to open  file to write\n");

    		
    		
    		foreach $commline (@COMMENTS) {
    			print(CCODE $commline);
    		
    		}   		
    		
    	#	print(CCODE  "extern ");
    		$kk=0;
    		$jj=0;
    		foreach $block (@sortedBlocks) {
    		
    		         print(CCODE "int ");
    		         print(CCODE  $block); 
    		         print(CCODE  "(int  run_state,block_Pt  block_P);\n"); 
    		 #   if($kk != $#sortedBlocks) {
    		 #   			print(CCODE  ",");
    		#    } else {
    		    
    		 #         print (CCODE ";");
    		#    }
    		#    if($jj==1) {
    		#       print(CCODE  "\n\t");
    		#       $jj=0;
    		    
    		 #   }
    		    $jj++;
    		    $kk++;
    			
    		
    		}


			print (CCODE "\n/* model table Definition */\n");
			print (CCODE "int model_count = "); print(CCODE  $#sortedBlocks+1); print(CCODE  ";\n");
			print (CCODE  "modelEntry_t model[MAX_MODELS] = {\n");
			print (CCODE "\n/* function, name, icon_id */\n");
			

    		$kk=0;
    		
    		foreach $block (@sortedBlocks) {
    		    print(CCODE  "{ "); print(CCODE  $block); print(CCODE  ","); print(CCODE  "\""); print(CCODE  $block); print(CCODE  "\"");
    		    print (CCODE ","); print (CCODE  "\""); print (CCODE substr($block,0,7)); print (CCODE "\""); print(CCODE  "}");
    		    if($kk != $#sortedBlocks) {
    		    			print (CCODE ",\n");
    		    } else {
    		    
    		          print (CCODE "\n};");
    		    }

    		    $kk++;
    			
    		
    		}    		
    		


			$file =~ s/://; # get rid of : at beginning of file name


                        print (CCODE "\n");			
			close(CCODE);
			
			$fil = "blockdatabase.dat";
#			&MacPerl'SetFileInfo("ttxt","TEXT",$fil);    
			
			
			$fil = "krn_blocklib.c";
#		&MacPerl'SetFileInfo("ttxt","TEXT",$fil);    
}




#
# prints a file in variable $file line by line
#
sub printFile {
    	open (INFILE, "$file") || die "could not open infile $f";
#    	print "\nProcessing $f\n"; # print a message to the STDOUT default output window
    	$linenum = 0;
    	# now read each line - it will go into $_
    	while (<INFILE>) {
        	print "line $linenum => $_";  # note $_ will includes a return at the end
                                      # we would say 'chop;' to get rid of it
        	$linenum++;  # increment our counter
    	}
    	# close it
    	close (INFILE);
}
__END__

