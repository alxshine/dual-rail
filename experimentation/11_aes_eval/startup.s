.global _Reset
_Reset:
 LDR sp, =stack_top
 BL balanced_c_entry
