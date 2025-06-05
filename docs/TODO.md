# NEBULA Engine Roadmap

This is an estimation of the features for each release version of the engine. Specific features might be moved around depending on the complexity.

## Release 0.1.0

- [x] Mesh
  - [x] Mesh creation
    - [x] VAO
    - [x] VBO
    - [x] EBO
    - [x] Shader
      - [x] Shader loading
      - [x] Shader compiling
- [x] Lighting
  - [x] Diffuse light
  - [x] Ambient light
  - [x] Specular light
    - [x] Specular maps
- [x] Logging
  - [x] Log to stdout

## Release 0.2.0

- [ ] Transition from OpenGL to Vulkan
  - [ ] Setup
    - [X] Base code
    - [X] Instance
    - [X] Validation Layers
    - [ ] Physical devices and queue families
    - [ ] Logical devices and queues
  - [ ] Presentation
    - [ ] Window Surface
    - [ ] Swap chain
    - [ ] Image views

## Release 0.2.1

- [ ] Shader
  - [ ] Shader hot-reloading
- [ ] API
  - [ ] Init functions
  - [ ] Drawing functions
  - [ ] Options
  - [ ] Cleanup functions
- [ ] Util
  - [ ] File path resolutions
- [ ] Mesh model loading
- [ ] Log to files

## Release 0.3.0

- [ ] Audio
