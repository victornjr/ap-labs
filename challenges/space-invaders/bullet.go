package main

import (
	"github.com/veandco/go-sdl2/sdl"
)

const (
	bulletSize  = 32
	bulletSpeed = 10
)

func newBullet(renderer *sdl.Renderer,tag string) *element {
	bullet := &element{}

	sr := newSpriteRenderer(bullet, renderer, "sprites/"+tag+".png")
	bullet.addComponent(sr)
	mover := newBulletMover(bullet)
	bullet.addComponent(mover)

	col := circle{
		center: bullet.position,
		radius: 8,
	}
	bullet.collisions = append(bullet.collisions, col)
	bullet.tag = tag

	return bullet
}

var bulletPool []*element

func initBulletPool(renderer *sdl.Renderer) {
	for i := 0; i < 50; i++ {
		bul := newBullet(renderer,"bullet")
		bulletPool = append(bulletPool, bul)
		elements = append(elements, bul)
	}
}

func bulletFromPool() (*element, bool) {
	for _, bul := range bulletPool {
		if !bul.active {
			return bul, true
		}
	}
	return nil, false
}
