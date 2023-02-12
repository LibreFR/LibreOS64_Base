NOMSE="LibreOS64"

if ! test -f "SE.flp"; then
    echo "SE.flp n'existe pas ; Veuillez d'abord compiler votre SE via ./run.sh"
fi

if test -f "SE.img"; then
    rm SE.img
fi

#Taille maximale du SE pour l'instant: 1 474 560 octets, soit environ 1,47 Mo
dd if=/dev/zero of=SE.img bs=1024 count=1440
dd if=SE.flp of=SE.img conv=notrunc seek=0

mkisofs -V "LibreOS64" -input-charset iso8859-1 -o SE.iso -b SE.flp .
