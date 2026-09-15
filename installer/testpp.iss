#define AppVersion "20.1.4"

#ifndef Arch
  #define Arch "x64"
#endif

[Setup]
AppName=Test++
AppVersion={#AppVersion}
AppPublisher=Oliver Lie
AppPublisherURL=https://github.com/olie-ver/TestPlusPlus
AppSupportURL=https://github.com/olie-ver/TestPlusPlus
AppUpdatesURL=https://github.com/olie-ver/TestPlusPlus
UninstallDisplayName=Test++

DefaultDirName={autopf}\testpp

#if Arch == "x86"
  ArchitecturesAllowed=x86
#elif Arch == "x64"
    ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64
#elif Arch == "arm64"
  ArchitecturesAllowed=arm64
  ArchitecturesInstallIn64BitMode=arm64
#else
  #error "Unsupported architecture. Use x86, x64, or arm64."
#endif

DisableProgramGroupPage=yes
ChangesEnvironment=yes

OutputDir=installs
OutputBaseFilename=TestPlusPlus-{#AppVersion}-win-{#Arch}

[Files]
Source: "..\V{#AppVersion}\staging\*"; DestDir: "{app}"; Flags: recursesubdirs createallsubdirs

#if Arch == "x86"
  Source: "VC_redist.x86.exe"; DestDir: "{tmp}"; Flags: deleteafterinstall
#elif Arch == "x64"
  Source: "VC_redist.x64.exe"; DestDir: "{tmp}"; Flags: deleteafterinstall
#elif Arch == "arm64"
  Source: "VC_redist.arm64.exe"; DestDir: "{tmp}"; Flags: deleteafterinstall
#endif

[Registry]
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; \
    ValueType: expandsz; ValueName: "Path"; ValueData: "{olddata};{app}\bin"; \
    Check: NeedsAddPath(ExpandConstant('{app}\bin')); Flags: preservestringtype

[Run]
#if Arch == "x86"
  Filename: "{tmp}\vc_redist.x86.exe"; \
#elif Arch == "x64"
  Filename: "{tmp}\vc_redist.x64.exe"; \
#elif Arch == "arm64"
  Filename: "{tmp}\vc_redist.arm64.exe"; \
#endif
    Parameters: "/install /quiet /norestart"; \
    StatusMsg: "Installing Microsoft Visual C++ Redistributable..."; \
    Check: ShouldInstallVCRedist(); \
    Flags: waituntilterminated

[Code]

function NeedsAddPath(Param: string): Boolean;
var
  ExistingPath: string;
begin
  if not RegQueryStringValue(
    HKEY_LOCAL_MACHINE,
    'SYSTEM\CurrentControlSet\Control\Session Manager\Environment',
    'Path',
    ExistingPath
  ) then
    ExistingPath := '';

  Result := Pos(';' + UpperCase(Param) + ';',
                 ';' + UpperCase(ExistingPath) + ';') = 0;
end;


function ShouldInstallVCRedist(): Boolean;
var
  InstalledVersion: string;
begin
  Result := not RegQueryStringValue(
    HKEY_LOCAL_MACHINE,
#if Arch == "x86"
    'SOFTWARE\Microsoft\VisualStudio\14.0\VC\Runtimes\x86',
#elif Arch == "x64"
    'SOFTWARE\Microsoft\VisualStudio\14.0\VC\Runtimes\x64',
#elif Arch == "arm64"
    'SOFTWARE\Microsoft\VisualStudio\14.0\VC\Runtimes\arm64',
#endif
    'Version',
    InstalledVersion
  );
end;


procedure RemovePathEntry(Param: string);
var
  ExistingPath: string;
  NewPath: string;
begin
  if not RegQueryStringValue(
    HKEY_LOCAL_MACHINE,
    'SYSTEM\CurrentControlSet\Control\Session Manager\Environment',
    'Path',
    ExistingPath
  ) then
    Exit;

  NewPath := ';' + ExistingPath + ';';

  StringChangeEx(
    NewPath,
    ';' + Param + ';',
    ';',
    True
  );

  NewPath := Copy(NewPath, 2, Length(NewPath) - 2);

  RegWriteExpandStringValue(
    HKEY_LOCAL_MACHINE,
    'SYSTEM\CurrentControlSet\Control\Session Manager\Environment',
    'Path',
    NewPath
  );
end;


procedure CurUninstallStepChanged(UninstallStep: TUninstallStep);
begin
  if UninstallStep = usPostUninstall then
    RemovePathEntry(ExpandConstant('{app}\bin'));
end;
