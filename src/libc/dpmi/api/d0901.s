/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include "dpmidefs.h"

	.text

	FUNC(___dpmi_get_and_enable_virtual_interrupt_state)
	ENTER

	movw	$0x0901, %ax
	int	$0x31
	movzbl	%al, %eax

	LEAVE
