#define AppVersion "20.1.4"

[Setup]
AppName=Test++
AppVersion={#AppVersion}
AppPublisher=Oliver Lie
AppPublisherURL=https://github.com/olie-ver/TestPlusPlus
AppSupportURL=https://github.com/olie-ver/TestPlusPlus/issues
AppUpdatesURL=https://github.com/olie-ver/TestPlusPlus/releases
UninstallDisplayName=Test++

DefaultDirName={autopf}\testpp
ArchitecturesAllowed=arm64
ArchitecturesInstallIn64BitMode=arm64
DisableProgramGroupPage=yes
ChangesEnvironment=yes

OutputDir=installs
OutputBaseFilename=TestPlusPlus-{#AppVersion}-win-arm64

[Files]
Source: "..\V{#AppVersion}\staging\*"; DestDir: "{app}"; Flags: recursesubdirs createallsubdirs
Source: "VC_redist.arm64.exe"; DestDir: "{tmp}"; Flags: deleteafterinstall

[Registry]
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; \
    ValueType: expandsz; ValueName: "Path"; ValueData: "{olddata};{app}\bin"; \
    Check: NeedsAddPath(ExpandConstant('{app}\bin')); Flags: preservestringtype

[Run]
Filename: "{tmp}\vc_redist.arm64.exe"; \
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
    'SOFTWARE\Microsoft\VisualStudio\14.0\VC\Runtimes\arm64',
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