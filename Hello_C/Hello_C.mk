##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=Hello_C
ConfigurationName      :=Release
WorkspaceConfiguration :=Release
WorkspacePath          :=/home/sergue/Документы/Top
ProjectPath            :=/home/sergue/Документы/Top/Hello_C
IntermediateDirectory  :=../build-$(WorkspaceConfiguration)/Hello_C
OutDir                 :=$(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Сергей
Date                   :=19/03/24
CodeLitePath           :=/home/sergue/.codelite
MakeDirCommand         :=mkdir -p
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputDirectory        :=/home/sergue/Документы/Top/build-$(WorkspaceConfiguration)/bin
OutputFile             :=../build-$(WorkspaceConfiguration)/bin/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG $(PreprocessorSwitch)_CONSOLE 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -O2 -Wextra $(Preprocessors)
CFLAGS   :=  -O2 -Wextra $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/up_hello.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) "$(IntermediateDirectory)"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "$(IntermediateDirectory)"
	@$(MakeDirCommand) "$(OutputDirectory)"

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "$(IntermediateDirectory)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/up_hello.c$(ObjectSuffix): ../hello.c 
	$(CC) $(SourceSwitch) "/home/sergue/Документы/Top/hello.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_hello.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_hello.c$(PreprocessSuffix): ../hello.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_hello.c$(PreprocessSuffix) ../hello.c

##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


