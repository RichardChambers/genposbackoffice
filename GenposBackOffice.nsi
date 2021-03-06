# NSIS installation compiler script
# See nullsoft scriptable install system at http://nsis.sourceforge.net/Download

Name "GenPOS Back Office"

# General Symbol Definitions
!define REGKEY "SOFTWARE\$(^Name)"
!define VERSION 1.0.0.001
!define COMPANY "Georgia Southern University"
!define URL https://github.com/RichardChambers/genposbackoffice

# couple of basic defined macros for paths for output and GPBOFILEDIR for NSIS compiler input directory
!define GPBOPATH  NCR\NeighborhoodPOS\genposbackoffice
!define GPBONNAME genposbackoffice
!define GPBOFILEDIR  release				# the solution target directory where things to package are located.

# MUI Symbol Definitions
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\orange-install.ico"
!define MUI_FINISHPAGE_NOAUTOCLOSE
!define MUI_LICENSEPAGE_RADIOBUTTONS
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\orange-uninstall.ico"
!define MUI_UNFINISHPAGE_NOAUTOCLOSE

# Included files
!include Sections.nsh
!include MUI2.nsh

# Variables
Var StartMenuGroup

# Installer pages
!insertmacro MUI_PAGE_WELCOME
#!insertmacro MUI_PAGE_LICENSE "License genposbackoffice.rtf"
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

# Installer languages
!insertmacro MUI_LANGUAGE English

# Installer attributes
OutFile GPBO_rel_01_00_00_001.exe
InstallDir $PROGRAMFILES\${GPBOPATH}
CRCCheck force
XPStyle on
ShowInstDetails show
ShowUninstDetails show

VIProductVersion "${VERSION}"
VIAddVersionKey ProductName "$(^Name)"
VIAddVersionKey ProductVersion "${VERSION}"
VIAddVersionKey CompanyName "${COMPANY}"
VIAddVersionKey CompanyWebsite "${URL}"
VIAddVersionKey FileVersion "${VERSION}"
VIAddVersionKey FileDescription ""
VIAddVersionKey LegalCopyright ""
InstallDirRegKey HKLM "${REGKEY}" Path

RequestExecutionLevel admin				# require admin security level for the install.

# Installer sections
Section -Main SEC0000
    SetOverwrite on
    
    SetOutPath $INSTDIR
    # following are generated files to include in the installer as well as Third Party Toolkit dlls.
    File /r ${GPBOFILEDIR}\*.exe				# include the executable file
    File /r ${GPBOFILEDIR}\*.dll				# include the dlls we need to run, Third Party Toolkit
    File /r ${GPBOFILEDIR}\*.ch*				# include the help files into the installer
    
    # following is the Visual Studio C++ Runtime redistributable. Actual location may vary!
    File "C:\Program Files (x86)\Microsoft Visual Studio 8\SDK\v2.0\BootStrapper\Packages\vcredist_x86\vcredist_x86.exe"

    CreateDirectory "$SMPROGRAMS\$StartMenuGroup"
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\GenPOS Back Office.lnk" $INSTDIR\${GPBONNAME}.exe

    #creates the filetype association for genposbackoffice settings documents
    WriteRegStr HKCR ".gpbo" "" "gpbo.Document"														#associate extension
    WriteRegStr HKCR "gpbo.Document" "" "GenPOS Backoff Settings File"								#give friendly name
    WriteRegStr HKCR "gpbo.Document\DefaultIcon" "" "$INSTDIR\GenposBackOffice.exe,0"				#set default icon
    WriteRegStr HKCR "gpbo.Document\shell\open\command" "" '"$INSTDIR\GenposBackOffice.exe" "%1"'	#set open command

#	ExecWait '"$INSTDIR\vcredist_x86.exe"'											#normal run (dialog with cancel button)
	ExecWait '"$INSTDIR\vcredist_x86.exe" /q:a /c:"msiexec /i vcredist.msi /qb!"'	#dialog with no cancel
#	ExecWait '"$INSTDIR\vcredist_x86.exe" /q:a /c:"msiexec /i vcredist.msi /qn"'	#totally silent

    WriteRegStr HKLM "${REGKEY}\Components" Main 1
SectionEnd

Section -post SEC0001
    Delete /REBOOTOK vcredist_x86.exe
    WriteRegStr HKLM "${REGKEY}" Path $INSTDIR
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe
    SetOutPath $SMPROGRAMS\$StartMenuGroup
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\Uninstall $(^Name).lnk" $INSTDIR\uninstall.exe
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayName "$(^Name)"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayVersion "${VERSION}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" Publisher "${COMPANY}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" URLInfoAbout "${URL}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayIcon $INSTDIR\uninstall.exe
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" UninstallString $INSTDIR\uninstall.exe
    WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" NoModify 1
    WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" NoRepair 1
SectionEnd

# Macro for selecting uninstaller sections
!macro SELECT_UNSECTION SECTION_NAME UNSECTION_ID
    Push $R0
    ReadRegStr $R0 HKLM "${REGKEY}\Components" "${SECTION_NAME}"
    StrCmp $R0 1 0 next${UNSECTION_ID}
    !insertmacro SelectSection "${UNSECTION_ID}"
    GoTo done${UNSECTION_ID}
next${UNSECTION_ID}:
    !insertmacro UnselectSection "${UNSECTION_ID}"
done${UNSECTION_ID}:
    Pop $R0
!macroend

# Uninstaller sections
Section /o -un.Main UNSEC0000
	
	#remove filetype association
	DeleteRegKey HKCR ".gpbo"
	DeleteRegKey HKCR "gpbo.Document"
	
    DeleteRegValue HKLM "${REGKEY}\Components" Main
SectionEnd

Section -un.post UNSEC0001
    DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)"
    Delete /REBOOTOK $INSTDIR\uninstall.exe
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\Uninstall $(^Name).lnk"
    DeleteRegValue HKLM "${REGKEY}" Path
    DeleteRegKey /IfEmpty HKLM "${REGKEY}\Components"
    DeleteRegKey /IfEmpty HKLM "${REGKEY}"
    
    # remove the installation directories
    RmDir /r /REBOOTOK $SMPROGRAMS\$StartMenuGroup
    RmDir /r /REBOOTOK $PROGRAMFILES\${GPBOPATH}
    
    # remove the parent directories if they are empty
    RmDir /REBOOTOK $PROGRAMFILES\NCR\NeighborhoodPOS
    RmDir /REBOOTOK $PROGRAMFILES\NCR
SectionEnd

# Installer functions
Function .onInit
    InitPluginsDir
    StrCpy $StartMenuGroup "$(^Name)"
FunctionEnd

# Uninstaller functions
Function un.onInit
    ReadRegStr $INSTDIR HKLM "${REGKEY}" Path
    StrCpy $StartMenuGroup "$(^Name)"
    !insertmacro SELECT_UNSECTION Main ${UNSEC0000}
FunctionEnd

