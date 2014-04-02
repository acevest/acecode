int="dddsafasdfasdf"
echo "AAA" >file
while [ $int != 5 ] 
do 
	sq="expr $int \* $int"
	echo $sq
	int="" 
done 
