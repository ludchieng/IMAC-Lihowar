# DEV

## Architecture

(s) means singleton

Initialization sequence :

```
main
├> glimac::SDLWindowManager
└> Game (s)
   └> GameController (s)
      ├> AssetManager (s)
      │  └> collection of Mesh
      │     └> foreach Mesh
      │        └> load .obj file
      │
      ├> GameRenderer (s)
      │  └> TrackBallCamera
      │
      └> collection of Object
         └> foreach Object
            ├> Program (s)
            └> Object::PRS
```

Rendering sequence :
```
main loop:
├> handle mouse/keyboard event
├> Game::render()
│  └> GameController::render()
│     └> foreach Object
│        ├> transform Object
│        ├> use program of Object
│        ├> update matrices MVP
│        ├> bind variables to GPU as uniform
│        └> draw Object
│
└> swap buffers
```


## Variable naming

`u`: uniform variable (e.g. `uMatModel`: model matrix as uniform variable) \
`g`: game (e.g. `gRenderer`: GameRenderer) \
`mat`: matrix (e.g. `matMV`: model view matrix) \
`tex`: texture \
`MVP`: model view projection (matrices) \
`tbcam`: trackball camera \
`prs`: position rotation scale