#!/usr/bin/bash

mkdir Donets.Nikolay.it6
cd Donets.Nikolay.it6
mkdir D.N.O.1
mkdir D.N.O.2
mkdir D.N.O.3

cd D.N.O.1

echo "Donets Nikolay Olegovich it6" > Donets.txt

cp Donets.txt ../D.N.O.2/Donets.txt 

cd ../D.N.O.2

mv Donets.txt stenoD.txt

cd ..

name=$1

if [ -z "$name" ]
then
	echo "Otec, mne nujno imya" | tee etolog.log
	read name
fi

cat D.N.O.1/Donets.txt D.N.O.2/stenoD.txt > D.N.O.3/$name.txt

mv D.N.O.3/$name.txt $name.txt

cat $name.txt | tee -a etolog.log
