DIR1=other/test_asm
RES=armres.out

INPUT=Rainbow_dash.s
OUTPUT=Rainbow_dash.cor
printf "\n\t$YELLOW$INPUT$NC\n"
./asm $DIR1/$INPUT
./other/42asm $DIR1/$INPUT
diff $DIR1/$OUTPUT $OUTPUT > $RES
rm $DIR1/$OUTPUT $OUTPUT
cat $RES


INPUT=NoIdea.s
OUTPUT=NoIdea.cor
printf "\n\t$YELLOW$INPUT$NC\n"
./asm $DIR1/$INPUT
./other/42asm $DIR1/$INPUT
cmp $DIR1/$OUTPUT $OUTPUT > $RES
rm $DIR1/$OUTPUT $OUTPUT
cat $RES


INPUT=tchupka.s
OUTPUT=tchupka.cor
printf "\n\t$YELLOW$INPUT$NC\n"
./asm $DIR1/$INPUT
./other/42asm $DIR1/$INPUT
cmp $DIR1/$OUTPUT $OUTPUT> $RES
rm $DIR1/$OUTPUT $OUTPUT
cat $RES


INPUT=run_Kitty_RUN.s
OUTPUT=run_Kitty_RUN.cor
printf "\n\t$YELLOW$INPUT$NC\n"
./asm $DIR1/$INPUT
./other/42asm $DIR1/$INPUT
cmp $DIR1/$OUTPUT $OUTPUT > $RES
rm $DIR1/$OUTPUT $OUTPUT
cat $RES


INPUT=Explosive_Kitty.s
OUTPUT=Explosive_Kitty.cor
printf "\n\t$YELLOW$INPUT$NC\n"
./asm $DIR1/$INPUT
./other/42asm $DIR1/$INPUT
cmp $DIR1/$OUTPUT $OUTPUT > $RES
rm $DIR1/$OUTPUT $OUTPUT
cat $RES


INPUT=O-Maley_Miaou.s
OUTPUT=O-Maley_Miaou.cor
printf "\n\t$YELLOW$INPUT$NC\n"
./asm $DIR1/$INPUT
./other/42asm $DIR1/$INPUT
cmp $DIR1/$OUTPUT $OUTPUT > $RES
rm $DIR1/$OUTPUT $OUTPUT
cat $RES


INPUT=Stargate0_1.s
OUTPUT=Stargate0_1.cor
printf "\n\t$YELLOW$INPUT$NC\n"
./asm $DIR1/$INPUT
./other/42asm $DIR1/$INPUT
cmp $DIR1/$OUTPUT $OUTPUT > $RES
rm $DIR1/$OUTPUT $OUTPUT
cat $RES


INPUT=zork.s
OUTPUT=zork.cor
printf "\n\t$YELLOW$INPUT$NC\n"
./asm $DIR1/$INPUT
./other/42asm $DIR1/$INPUT
cmp $DIR1/$OUTPUT $OUTPUT > $RES
rm $DIR1/$OUTPUT $OUTPUT
cat $RES


INPUT=Hidden.s
OUTPUT=Hidden.cor
printf "\n\t$YELLOW$INPUT$NC\n"
./asm $DIR1/$INPUT
./other/42asm $DIR1/$INPUT
cmp $DIR1/$OUTPUT $OUTPUT > $RES
rm $DIR1/$OUTPUT $OUTPUT
cat $RES

echo "\n"
read -p "Клац  >> " wait
echo "clear all"
rm $RES