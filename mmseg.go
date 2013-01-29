package mmseg

/*
#cgo LDFLAGS: -L. -lgommseg
#include <stdlib.h>
#include "mmseg.h"
*/
import "C"
import (
	"errors"
	"unsafe"
)

func Init(path string) error {
	p := C.CString(path)
	defer C.free(unsafe.Pointer(p))
	ret := C.mmseg_init(p)
	if int(ret) < 0 {
		return errors.New("init error")
	}
	return nil
}

func Segment(text string) ([]string, error) {
	ctext := C.CString(text)
	defer C.free(unsafe.Pointer(ctext))

	var cret *C.Token
	n := int(C.mmseg_segment(ctext, &cret))
	if n < 0 {
		return nil, errors.New("segment error")
	}
	ret := make([]string, n)
	p := cret
	for i := 0; i < n; i++ {
		ret[i] = C.GoStringN(p.Start, p.Len)
		p = C.next_token(p)
	}
	C.free(unsafe.Pointer(cret))
	return ret, nil
}

func Destroy() {
	C.mmseg_destroy()
}
