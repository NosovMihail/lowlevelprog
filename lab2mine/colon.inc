%define last_add 0

%macro colon 2
%2:
	dq last_add
	db %1, 0
%define last_add %2
%endmacro
