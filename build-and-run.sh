#!/usr/bin/env bash

readonly _debug=yes
readonly _build_directory="build"
readonly _default_build_target="Debug"
readonly _default_build_tool="Ninja"
readonly _executable_to_run="asteroids"

function debug() {
  if [[ ${_debug} == "yes" ]]; then
    printf '[DEBUG] %s\n' "$@"
  fi
}

function die() {
  printf '[ERROR] %s\n' "$@" >&2
  exit 1
}

function parse_arguments() {
  opt_build_target=${_default_build_target}
  opt_build_tool=${_default_build_tool}
  opt_clean="no"
  while [[ "$#" -gt 0 ]]; do
    case $1 in
      -c|--clean)
        opt_clean=yes
        ;;
      -t|--target)
        opt_build_target="${2}"
        if [[ ${opt_build_target} != "debug" && ${opt_build_target} != "release" ]]; then
          die "Unknown 'target' parameter value: ${opt_build_target}"
        fi
        shift
        ;;
      *)
        die "Unknown parameter passed: $1"
        ;;
    esac
    shift
  done
}

function on_exit() {
  popd 2>/dev/null
}

## SCRIPT ENTRYPOINT

trap on_exit EXIT

[[ ! -f "./build-and-run.sh" ]] && die "Script runnable only from project root directory"

parse_arguments "$@"

readonly target_build_directory="./${_build_directory}/${opt_build_target,,}"

if [[ ! -d ${target_build_directory} || ${opt_clean} == "yes" ]]; then
  rm -fr ${target_build_directory} || die "Could not remove ${target_build_directory} directory"
  mkdir -p "${target_build_directory}" || die "Could not create ${target_build_directory} directory"

  pushd .
  cd "${target_build_directory}" || die "Could not change directory into ${target_build_directory}"
  already_inside_build_directory=yes

  echo ">>> Running CMake..."
  cmake ../.. -DCMAKE_BUILD_TYPE="${opt_build_target}" -G"${opt_build_tool}"
fi

if [[ ${already_inside_build_directory} != "yes" ]]; then
  pushd .
  cd "${target_build_directory}" || die "Could not change directory into ${target_build_directory}"
fi

# build binaries / executables
echo ">>> Building binaries..."
${opt_build_tool,,} || die "Building binaries failed"

# run main executable
cd bin
./${_executable_to_run}
