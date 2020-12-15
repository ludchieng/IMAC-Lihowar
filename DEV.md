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
      │  └> collection of Model
      │     └> foreach Model
      │        └> load .obj file
      │
      ├> GameRenderer (s)
      │  └> TrackBallCamera
      │
      └> collection of GameObject
         └> foreach GameObject
            ├> Program (s)
            └> GameObject::PRS
```

Rendering sequence :
```
main loop:
├> handle mouse/keyboard event
├> Game::render()
│  └> GameController::render()
│     └> foreach GameObject
│        ├> transform GameObject
│        ├> use program of GameObject
│        ├> update matrices MVP
│        ├> bind variables to GPU as uniform
│        └> draw GameObject
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