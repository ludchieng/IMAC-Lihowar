²# DEV

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
      │  └> collection of Texture
      │     └> foreach Texture
      │        └> load texture
      │
      ├> GameRenderer (s)
      │  └> TrackBallCamera
      │
      └> collection of Object
         └> foreach Object
            ├> Program (s)
            └> Object::PRS
```

Game loop sequence :
```
main loop:
├> handle mouse/keyboard event
├> Game::update()
│  └> Pump and process SDL events (keyboard and joystick)
│  └> GameController::update()
│     └> update skybox position
│     └> update objects dynamics (apply forces or torques)
│     └> update scene objects
│
├> Game::render()
│  └> GameController::render()
│     └> GameRenderer::render(scene)
│        └> render each scene objects
│           ├> update model and view matrices
│           ├> bind variables to GPU as uniform
│           ├> draw object
│           └> draw its subobjects
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

`acc`: acceleration \
`vel`: velocity \
`pos`: position \
`ang`: angle or angular


`diff`: diffuse map \
`spec`: specular map \
`lumin`: luminance map \
`ao`: ambient occlusion map \
`normal`: normal map