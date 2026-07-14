# Compile the latest changes
.\make.ps1

# If compilation succeeded, run the executable instantly
if ($LASTEXITCODE -eq 0) {
    ./build/game.exe
}