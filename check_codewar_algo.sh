YELLOW='\033[0;33m'
NC='\033[0m' # No Color

DIR1=other/valid_champs
OUT1=cw.out
OUT2=cw42.out
RES=res.out
OPTION="-v 4 -a"

INPUT=Explosive_Kitty.cor
printf "\n\t$YELLOW$INPUT$NC\n"
./corewar $DIR1/$INPUT $OPTION > cw.out
./other/42corewar $DIR1/$INPUT $OPTION > cw42.out
diff $OUT1 $OUT2 > $RES
cat $RES

echo "\n"
read -p "Клац  >> " wait

INPUT=NoIdea.cor
printf "\n\t$YELLOW$INPUT$NC\n"
./corewar $DIR1/$INPUT $OPTION > cw.out
./other/42corewar $DIR1/$INPUT $OPTION > cw42.out
diff $OUT1 $OUT2 > $RES
cat $RES

echo "\n"
read -p "Клац  >> " wait

INPUT="NoIdea.cor tchupka.cor run_Kitty_RUN.cor"
printf "\n\t$YELLOW$INPUT$NC\n"
./corewar $DIR1/NoIdea.cor $DIR1/tchupka.cor $DIR1/run_Kitty_RUN.cor $OPTION > cw.out
./other/42corewar $DIR1/NoIdea.cor $DIR1/tchupka.cor $DIR1/run_Kitty_RUN.cor $OPTION > cw42.out
diff $OUT1 $OUT2 > $RES
cat $RES

echo "\n"
read -p "Клац  >> " wait

INPUT="Explosive_Kitty.cor O-Maley_Miaou.cor Stargate0_1.cor lapsang.cor"
printf "\n\t$YELLOW$INPUT$NC\n"
./corewar $DIR1/Explosive_Kitty.cor $DIR1/O-Maley_Miaou.cor $DIR1/Stargate0_1.cor $DIR1/lapsang.cor $OPTION > cw.out
./other/42corewar $DIR1/Explosive_Kitty.cor $DIR1/O-Maley_Miaou.cor $DIR1/Stargate0_1.cor $DIR1/lapsang.cor $OPTION > cw42.out
diff $OUT1 $OUT2 > $RES
cat $RES

echo "\n"
read -p "Клац  >> " wait

INPUT="zork.cor Hidden.cor NoIdea.cor TheHarvester.cor"
printf "\n\t$YELLOW$INPUT$NC\n"
./corewar $DIR1/zork.cor $DIR1/Hidden.cor $DIR1/NoIdea.cor $DIR1/TheHarvester.cor $OPTION > cw.out
./other/42corewar $DIR1/zork.cor $DIR1/Hidden.cor $DIR1/NoIdea.cor $DIR1/TheHarvester.cor $OPTION > cw42.out
diff $OUT1 $OUT2 > $RES
cat $RES

echo "\n"
read -p "Клац  >> " wait
echo "clear all"
rm $OUT1 $OUT2 $RES