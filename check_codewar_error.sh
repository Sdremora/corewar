MAP=other/inv_input/inv_end_on_magic.cor
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP=other/inv_input/inv_magic.cor
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP=other/inv_input/inv_end_on_name.cor
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP=other/inv_input/inv_end_on_null_section_1.cor
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP=other/inv_input/inv_end_on_null_section_1.cor
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP=other/inv_input/inv_null_section_1.cor
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP=other/inv_input/inv_end_on_size.cor
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP=other/inv_input/inv_size_section_minus_1.cor
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP=other/inv_input/inv_size_section_over.cor
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP=other/inv_input/inv_size_section_zero.cor
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP=other/inv_input/inv_end_on_comment.cor
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP=other/inv_input/inv_end_on_null_section_2.cor
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP=other/inv_input/inv_null_section_2.cor
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP=other/inv_input/inv_size_less.cor
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP=other/inv_input/inv_size_greater.cor
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP="-dump 100 -a"
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP="other/valid_champs/Explosive_Kitty.cor other/valid_champs/helltrain.cor other/valid_champs/Hidden.cor other/valid_champs/lapsang.cor other/valid_champs/O-Maley_Miaou.cor"
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP="other/valid_champs/opachki_nevalidnui_path.cor"
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP="other/valid_champs/Explosive_Kitty.cor other/valid_champs/helltrain.cor -n -1 other/valid_champs/Hidden.cor other/valid_champs/lapsang.cor"
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP="other/valid_champs/Explosive_Kitty.cor -n 2 other/valid_champs/helltrain.cor -n 0 other/valid_champs/Hidden.cor other/valid_champs/lapsang.cor"
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"

MAP="other/valid_champs/Explosive_Kitty.cor -n 2 other/valid_champs/helltrain.cor -n 2 other/valid_champs/Hidden.cor -n 99999999999999999999999999 other/valid_champs/lapsang.cor"
printf "./corewar $MAP\n %s\n\n" "$(./corewar $MAP)"