SECTIONS
{
        .text : {
	_kickstart_begin = .;
        *(.mbh)
        *(.text)
        *(.*data*)
        *(.*eh_frame*)
        _edata = .;
        }
        _end = .;
	_kickstart_end = .;
}
