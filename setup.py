#!/usr/bin/env python3


import os
import subprocess
import shutil
from pathlib import Path
import argparse


this_dir = Path(__file__).parent.resolve()


def _cmake(*args, **kwargs):
	p = subprocess.Popen(["cmake", *args], **kwargs)
	return p.wait()

def _msbuild(*args, **kwargs):
	p = subprocess.Popen(["msbuild", *args], **kwargs)
	return p.wait()


def _instantiateTemplates(dir):
	for p in os.scandir(dir):
		if p.is_dir():
			_instantiateTemplates(p.path)
		else:
			name, ext = os.path.splitext(p.path)
			if ext == ".template" and not os.path.exists(name):
				print(p.path)
				shutil.copy2(p.path, name)

def _build(project_file, *, platforms, configurations, targets = []):
	for platform in platforms:
		for configuration in configurations:
			args = []
			if targets:
				args.append(f"/t:{';'.join(targets)}")
			if _msbuild("/m", f"/p:Platform={platform}", f"/p:Configuration={configuration}", *args, project_file.resolve().as_posix()) != 0:
				raise Exception("build error")


class Subproject:
	def __init__(self, dir):
		self.root_dir = this_dir/dir

class SceneProcessor(Subproject):
	def __init__(self):
		super().__init__("sceneprocessor")
	
	def configure(self):
		_instantiateTemplates(self.root_dir)
	
	def _buildTootle(self, deps_dir):
		tootle_dir = deps_dir/"tootle"
		tootle_build_dir = tootle_dir/"build"/"vs2017"
		tootle_build_dir.mkdir(parents=True, exist_ok=True)
		cmake_flags = [
			f"-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG={deps_dir}/tootle/build/vs2017/lib",
			f"-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE={deps_dir}/tootle/build/vs2017/lib",
			"-DCMAKE_DEBUG_POSTFIX=D"
		]
		_cmake("-G", "Visual Studio 15 2017 Win64", *cmake_flags, "../../src", cwd=tootle_build_dir)
		_build(tootle_build_dir/"TootleLib"/"TootleLib.vcxproj", platforms=["x64"], configurations=["Debug", "Release"])
	
	def _buildDirectXMesh(self, deps_dir):
		directxmesh_dir = deps_dir/"directxmesh"
		_build(directxmesh_dir/"DirectXMesh_Desktop_2017_Win10.sln", platforms=["x64"], configurations=["Debug", "Release"], targets=["DirectXMesh"])
	
	def buildDependencies(self):
		deps_dir = self.root_dir/"build/dependencies"
		self._buildTootle(deps_dir)
		self._buildDirectXMesh(deps_dir)


class Visualizer(Subproject):
	def __init__(self):
		super().__init__("visualizer")

	def configure(self):
		_instantiateTemplates(self.root_dir)

	def buildDependencies(self):
		deps_dir = self.root_dir/"build/dependencies"
		_build(deps_dir/"COFF_tools/dotNET/COFF_tools.sln", platforms=["Any CPU"], configurations=["Release"])
		_build(deps_dir/"Win32_core_tools/build/vs2017/Win32_core_tools.vcxproj", platforms=["x64"], configurations=["Debug", "Release"])
		_build(deps_dir/"COM_core_tools/build/vs2017/COM_core_tools.vcxproj", platforms=["x64"], configurations=["Debug", "Release"])
		_build(deps_dir/"image_tools/build/vs2017/image_tools.vcxproj", platforms=["x64"], configurations=["Debug", "Release"])
		_build(deps_dir/"GL_platform_tools/build/vs2017/glcore.vcxproj", platforms=["x64"], configurations=["Debug", "Release", "Debug DLL", "Release DLL"])
		_build(deps_dir/"GL_platform_tools/build/vs2017/GL_platform_tools.vcxproj", platforms=["x64"], configurations=["Debug", "Release", "Debug DLL", "Release DLL"])
		_build(deps_dir/"config_tools/build/vs2017/config_tools.vcxproj", platforms=["x64"], configurations=["Debug", "Release"])
		_build(deps_dir/"GL_core_tools/build/vs2017/GL_core_tools.vcxproj", platforms=["x64"], configurations=["Debug", "Release", "Debug DLL", "Release DLL"])
		_build(deps_dir/"GLSL_build_tools/build/vs2017/GLSL_build_tools.sln", platforms=["x64"], configurations=["Release"])


project_map = {
	"sceneprocessor" : SceneProcessor,
	"visualizer" : Visualizer
}

def main(args):
	for project in args.projects:
		proj_type = project_map.get(project)

		if not proj_type:
			raise Exception("unknown project '" + proj_type + "'")

		proj = proj_type()
		proj.configure()
		proj.buildDependencies()


	# print("instantiating templates...")
	# _instantiateTemplates(this_dir)

	# print("building dependencies...")
	# _buildDependencies()
	# print("...done")


if __name__ == "__main__":
	parser = argparse.ArgumentParser()
	parser.add_argument("projects", nargs="*", default=["sceneprocessor", "visualizer"], metavar="project")
	main(parser.parse_args())
