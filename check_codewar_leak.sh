YELLOW='\033[0;33m'
NC='\033[0m' # No Color

DIR1=other/inv_input
DIR2=other/valid_champs

INPUT=inv_end_on_magic.cor
printf "\n\t$YELLOW$INPUT$NC\n"
valgrind ./corewar $DIR1/$INPUT 2>&1
echo "\n"
read -p "Клац  >> " wait

INPUT=inv_size_greater.cor
printf "\n\t$YELLOW$INPUT$NC\n"
valgrind ./corewar $DIR1/$INPUT 2>&1
echo "\n"
read -p "Клац  >> " wait

INPUT=inv_size_less.cor
printf "\n\t$YELLOW$INPUT$NC\n"
valgrind ./corewar $DIR1/$INPUT 2>&1
echo "\n"
read -p "Клац  >> " wait

INPUT=inv_size_section_minus_1.cor
printf "\n\t$YELLOW$INPUT$NC\n"
valgrind ./corewar $DIR1/$INPUT 2>&1
echo "\n"
read -p "Клац  >> " wait

INPUT=inv_size_less.cor
printf "\n\t$YELLOW$INPUT$NC\n"
valgrind ./corewar $DIR1/$INPUT 2>&1
echo "\n"
read -p "Клац  >> " wait

INPUT=valid_null_code.cor
printf "\n\t$YELLOW$INPUT$NC\n"
valgrind ./corewar $DIR2/$INPUT 2>&1
echo "\n"
read -p "Клац  >> " wait

INPUT="-dump 100 -a"
printf "\n\t$YELLOW$INPUT$NC\n"
valgrind ./corewar $DIR2/$INPUT 2>&1
echo "\n"
read -p "Клац  >> " wait

INPUT="other/valid_champs/opachki_nevalidnui_path.cor"
printf "\n\t$YELLOW$INPUT$NC\n"
valgrind ./corewar $DIR2/$INPUT 2>&1
echo "\n"
read -p "Клац  >> " wait

INPUT="other/valid_champs/Explosive_Kitty.cor other/valid_champs/helltrain.cor other/valid_champs/Hidden.cor other/valid_champs/lapsang.cor other/valid_champs/O-Maley_Miaou.cor"
printf "\n\t$YELLOW$INPUT$NC\n"
valgrind ./corewar $DIR2/$INPUT 2>&1
echo "\n"
read -p "Клац  >> " wait

INPUT=Explosive_Kitty.cor
printf "\n\t$YELLOW$INPUT$NC\n"
valgrind ./corewar $DIR2/$INPUT 2>&1
echo "\n"
read -p "Клац  >> " wait

INPUT="Explosive_Kitty.cor helltrain.cor"
printf "\n\t$YELLOW$INPUT$NC\n"
valgrind ./corewar $DIR2/Explosive_Kitty.cor $DIR2/helltrain.cor 2>&1
echo "\n"
read -p "Клац  >> " wait

INPUT="-n 2 Explosive_Kitty.cor -n 3 helltrain.cor run_Kitty_RUN.cor"
printf "\n\t$YELLOW$INPUT$NC\n"
valgrind ./corewar -n 2 $DIR2/Explosive_Kitty.cor -n 3 $DIR2/helltrain.cor $DIR2/run_Kitty_RUN.cor 2>&1
echo "\n"
read -p "Клац  >> " wait

INPUT="Hidden.cor -n 4 O-Maley_Miaou.cor tchupka.cor -n 2 NoIdea.cor"
printf "\n\t$YELLOW$INPUT$NC\n"
valgrind ./corewar $DIR2/Hidden.cor -n 4 $DIR2/O-Maley_Miaou.cor $DIR2/tchupka.cor -n 2 $DIR2/NoIdea.cor 2>&1