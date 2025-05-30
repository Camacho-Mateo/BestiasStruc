[Setup]
AppName=Sistema Bancario
AppVersion=1.0
DefaultDirName={pf}\Sistema Bancario BestiasStruck
DefaultGroupName=Sistema Bancario
OutputBaseFilename=instalador_sistema_bancario
Compression=lzma
SolidCompression=yes

[Files]
Source: "C:\Users\mateo\OneDrive\Escritorio\proyect_OPP\estructuraProject\BestiasStruc\ProyectoBanco\3.Code\BanckSystem\bin\bancario.exe"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\Sistema Bancario"; Filename: "{app}\bancario.exe"
Name: "{commondesktop}\Sistema Bancario"; Filename: "{app}\bancario.exe"; Tasks: desktopicon

[Tasks]
Name: "desktopicon"; Description: "Crear acceso directo en el escritorio"; GroupDescription: "Iconos adicionales:"; Flags: unchecked

[Code]
var
  ProductKeyPage: TInputQueryWizardPage;

function IsValidProductKey(Key: String): Boolean;
begin
  Result := Key = 'BANK-1234-5678-ACTV';
end;

procedure InitializeWizard;
begin
  ProductKeyPage := CreateInputQueryPage(wpWelcome,
    'Clave de Activación',
    'Ingrese la clave del producto para continuar',
    'Por favor, introduzca la clave de activación proporcionada para instalar Sistema Bancario.');

  ProductKeyPage.Add('Clave del Producto:', False);
end;

function NextButtonClick(CurPageID: Integer): Boolean;
begin
  Result := True;
  if CurPageID = ProductKeyPage.ID then
  begin
    if not IsValidProductKey(ProductKeyPage.Values[0]) then
    begin
      MsgBox('La clave introducida no es válida.', mbError, MB_OK);
      Result := False;
    end;
  end;
end;

