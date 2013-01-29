package mmseg

import (
	"testing"
)

func TestSegment(t *testing.T) {
	err := Init("data")
	if err!=nil {
		t.Fatal(err)
	}
	tokens, err := Segment("研究生命起源")
	if err!=nil {
		t.Fatal(err)
	}
	if len(tokens)!=3 || tokens[0]!="研究" || tokens[1]!="生命" || tokens[2]!="起源" {
		t.Fatal("segment not correct")
	}
	Destroy()
}
