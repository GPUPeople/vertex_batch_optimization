
Code for the rendering order optimization tools and experiments to go with the paper [*Revisiting The Vertex Cache: Understanding and Optimizing Vertex Processing on the modern GPU*][1].

The project consists of a main sceneprocessor application, a separate vertex cache test utility, a visualizer application, and various scripts to run experiments. The sceneprocessor application reads triangle meshes from Wavefront `.obj` files and applies various kinds of processing before writing out the resulting triangle mesh either to another `.obj` file or to the custom `.scene` format used by other tools in this project.

> Note: The project does contain quite a few components not mentioned in this readme. If a component is not explicitly mentioned here, the reason for this is most likely that the component in question is not currently in an operational state.


## How to build

Only Windows 10 (64-Bit) is currently supported. Building the project requires

  * Visual Studio 2017 (15.7+),
  * Windows SDK 10.0.17763.0,
  * Python 3.6+.

To initialize the build system and build dependencies, run `setup.py` from a Visual Studio 2017 Command Prompt. Once this is done, you can open `sceneprocessor/build/vs2017/sceneprocessor.sln` and `visualizer/build/vs2017/visualizer.sln`. The project relies on a few libraries, including [boost][2] (for a Fibonacci Heap implementation), and [AMD Tootle][3] and [DirectXMesh][4] (for implementations of various common vertex cache optimization algorithms). All necessary dependencies are included in the `build/dependencies` subdirectories of the respective subprojects.


## Sceneprocessor

The sceneprocessor utility reads a triangle mesh from the given source file and applies a sequence of operations defined by *layers*. A layer can perform a simple geometric or topological modification on the mesh, simply compute and print some statistics, write results to a new mesh file, or, most importantly, implement a particular triangle order optimization. The operations to carry out are specified via command line arguments as follows:

```
sceneconverter [-o <target-file>] [{[-t] -p <processing-layer>}] <source-file>
```

`-p` adds a processing layer of the given type. `-t` adds a timing layer (prints time elapsed since processing reached the previous timing layer or the start of the program). `-o` adds a terminating output layer which will write the resulting mesh to the specified file.

Effectively, the command line represents a pipeline where data flows through a stack of layers from right to left. The last, rightmost argument specifies the input file; the first, leftmost argument can specify an optional output file. Arguments in between specify processing layers or points where a timestamp should be taken. Supported processing layers:

   * basic mesh operations
       * `zflip` flip z-axis
       * `woflip` flip triangle winding order
       * `weld` deduplicate vertices
       * `unweld` duplicate vertices
   * triangle order
       * `randi` randomize order of triangles
       * `hoppe<N>` optimization method by [Hoppe [1999]][Hoppe1999] for cache size `<N>`
       * `linyu<N>` optimization method by [Lin and Yu [2006]][LinYu2006] for cache size `<N>`
       * `tipsify<N>` optimization method by [Sander et. al [2007]][Sander2007] for cache size `<N>`
       * `tomf` optimization method by [Tom Forsyth [2006]][TomF2006]
       * `mtomf` modified version of `tomf` which resets vertex scores after 96 indices
       * `sbatch` batch-based optimization
       * `ssbatch` batch-based optimization
       * `dbatch` batch-based optimization
       * `gbatch` batch-based optimization
       * `gbatchND` batch-based optimization
       * `gbatch.intel` batch-based optimization
       * `gbatchND.intel` batch-based optimization
       * `gbatch.amd` batch-based optimization
       * `gbatchND.amd` batch-based optimization
   * statistics
       * `vcs` print vertex reuse statistics
       * `ccachesim<N>` central vertex cache simulation for cache size `<N>`
       * `LRUcachesim<N>` LRU vertex cache simulation for cache size `<N>`
       * `vcachesim` vertex cache simulation
       * `enumbatch`

For example, the command line

```
sceneconverter -o bunny.scene -p vcs -t -p tomf -t -p randi -p vcs bunny.obj
```

would read the file `bunny.obj`, compute and print the vertex reuse statistics for the input file, randomize the order of triangles, print the time elapsed since the start of the program, perform triangle order optimization using the algorithm by Tom Forsyth, print the time elapsed since the last time the time was printed (effectively the time it took to run the optimization algorithm), compute and print the vertex reuse statistics of the optimized mesh, and finally output the optimized mesh to `bunny.scene`.


## Vertex Cache Test

The vertex cache test utility is a separate project, residing in its own repository. It is included in this project as a Git submodule. For more detail, consult the readme located in the respective repository.

## Visualizer

The visualizer application is used to display various visualizations illustrating the behavior of vertex cache optimization algorithms on a given mesh. The visualizations are based on information about how many times a given vertex was shaded and sets of vertices that were processed as a group. This kind of information is generated by other tools part of this project and stored in `.vsi` files (see the vertex cache test project for details on the file format). To start the visualizer application:

```
visualizer [-screen <screenshot-name>] [--prediction <vsi-file>] [--info <vsi-file>] <scene-file>
```

At least an argument specifying the `.scene` file to display is required. The `--info` and `--prediction` options can be used to specify `.vsi` files that contain the vertex processing statistics to visualize. `--info` specifies the base data set, `--prediction` can specify an additional data set to compare to. Instead of the name of a `.vsi` file, each option may alternatively specify the path of a directory. When given the path of a directory, the program will look for a `.vsi` file of the same name as the scene being used in the given directory. If no `.vsi` file is specified, the program will look for a `.vsi` file in the directory of the scene file. The `-screen` option can be used to save a screenshot to a file of the given name.

### Controls

  * left mouse:     drag to turn camera
  * middle mouse:   drag to pan camera
  * right mouse:    drag to zoom
  * `[Backspace]`   reset camera
  * `[Tab]`         cycle through different visualizations
  * `[F8]`          take screenshot
  * `[T]`           toggle triangle order curve
  * `[S]`           toggle batch silhouettes
  * `[W]`           toggle wireframe
  * `[B]`           toggle single batch mode
  * `[⇦][⇨]`       change focus batch
  * `[⇧][⇩]`        change focus batch (larger increment)



[1]: https://dl.acm.org/citation.cfm?id=3233302
[2]: https://github.com/boostorg/boost
[3]: https://github.com/GPUOpen-Tools/amd-tootle
[4]: https://github.com/Microsoft/DirectXMesh
[Hoppe1999]: https://dl.acm.org/citation.cfm?doid=311535.311565
[TomF2006]: https://tomforsyth1000.github.io/papers/fast_vert_cache_opt.html
[LinYu2006]: https://ieeexplore.ieee.org/document/1634327
[Sander2007]: https://dl.acm.org/citation.cfm?doid=1276377.1276489
