# hardbound-vp

A virtual prototype based on [riscv-vp][riscv-vp github] with [symbolic execution][wikipedia symex] support.

## About

This is a fork of [symex-vp][symex-vp github] which provides a
[HardBound][hardbound poi]-based path analyzer for finding spatial
memory safety violations in low-level code for constrained devices using
symbolic execution. The implementation is further described in the 2022
[ASP-DAC][asp-dac web] publication *Automated Detection of Spatial
Memory Safety Violations for Constrained Devices*.

## Installation

Refer to the original symex-vp [cloning][symex-vp clone] and
[installation][symex-vp install] instructions.

## Acknowledgements

This work was supported in part by the German Federal Ministry of
Education and Research (BMBF) within the project Scale4Edge under
contract no. 16ME0127 and within the project VerSys under contract
no. 01IW19001.

## License

The original riscv-vp code is licensed under MIT (see `LICENSE.MIT`).
All modifications made for the integration of symbolic execution with
riscv-vp are licensed under GPLv3+ (see `LICENSE.GPL`). Consult the
copyright headers of individual files for more information.

[riscv-vp github]: https://github.com/agra-uni-bremen/riscv-vp
[wikipedia symex]: https://en.wikipedia.org/wiki/Symbolic_execution
[z3 repo]: https://github.com/Z3Prover/z3
[llvm website]: https://llvm.org/
[cmake website]: https://cmake.org/
[boost website]: https://www.boost.org/
[sifive hifive1]: https://www.sifive.com/boards/hifive1
[riot website]: https://riot-os.org/
[zephyr website]: https://riot-os.org/
[riscv-compliance github]: https://github.com/riscv/riscv-compliance/
[symex-vp github]: https://github.com/agra-uni-bremen/symex-vp
[symex-vp clone]: https://github.com/agra-uni-bremen/symex-vp/blob/7fd4dbaba2dac28b9c51fd1c3edfa78ac112c668/README.md#cloning
[symex-vp install]: https://github.com/agra-uni-bremen/symex-vp/blob/7fd4dbaba2dac28b9c51fd1c3edfa78ac112c668/README.md#installation
[hardbound doi]: https://doi.org/10.1145/1353535.1346295
[asp-dac web]: https://aspdac2022.github.io/index.html
