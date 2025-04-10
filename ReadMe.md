<b>To run an OpenMp .c file: </b>
<br />gcc name_of_file.c -fopenmp -o alias 
<br />./alias file_passed_as_argument.txt

<br /><b>To run a MPI .c file: </b>
<br />mpicc name_of_file.c -o alias -lm
<br />mpiexec -np number_of_cores ./alias

