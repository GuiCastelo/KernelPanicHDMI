SECTIONS {
  .init 0x8000 : {
    *(.init)
  }
  
  .text : {
    *(.text)
    . = ALIGN(8);
    *(.rodata)
  }
  
  .data : {
    *(.data)
    . = ALIGN(8);
    _edata = .;
  }
  
  _bss_start_ = .;
  .bss : {
    *(.bss)
    . = ALIGN(8);
  }
  _bss_end_ = .;

  . = ALIGN(8);
  heap_addr = .;
  . = . + 32K;
  _stack_top_ = .;
  . = . + 4K;
  _stack_irq = .;

  _end_ = .;
}
