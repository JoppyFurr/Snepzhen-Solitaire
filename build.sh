#!/bin/sh
echo ""
echo "Snepzhen Solitaire Build Script"
echo "-------------------------------"

sdcc="${HOME}/Code/sdcc-4.3.0/bin/sdcc"
devkitSMS="${HOME}/Code/devkitSMS"
SMSlib="${devkitSMS}/SMSlib"
ihx2sms="${devkitSMS}/ihx2sms/Linux/ihx2sms"
sneptile="./tools/Sneptile-0.1.0/Sneptile"

build_sneptile ()
{
    # Early return if we've already got an up-to-date build
    if [ -e $sneptile -a "./tools/Sneptile-0.1.0/source/main.c" -ot $sneptile ]
    then
        return
    fi

    echo "Building Sneptile..."
    (
        cd "tools/Sneptile-0.1.0"
        ./build.sh
    )
}

build_snepzhen ()
{
    echo "Building Snepzhen Solitaire..."

    echo "  Generating tile data..."
    mkdir -p tile_data
    (
        # Note: Index 0 is used for transparency. An unused colour 0x0f is used as a place-holder.
        #       Index 1 is used for the card outlines, which can change at runtime.
        $sneptile --output tile_data --palette 0x0f 0x19 \
            tiles/empty.png \
            tiles/cursor.png \
            tiles/card-outline.png \
            tiles/card-blank.png \
            tiles/corner-numbers.png \
            tiles/corner-prints.png \
            tiles/corner-snep.png \
            tiles/chinese-numbers.png \
            tiles/footer.png \
            tiles/prints.png \
            tiles/snep-card.png \
            tiles/dragon-buttons.png \
            tiles/menu-text.png \
            tiles/menu-icons.png
    )

    mkdir -p build
    echo "  Compiling..."
    for file in main save rng
    do
        echo " -> ${file}.c"
        ${sdcc} -c -mz80 --peep-file ${devkitSMS}/SMSlib/src/peep-rules.txt -I ${SMSlib}/src \
            -o "build/${file}.rel" "source/${file}.c" || exit 1
    done

    echo ""
    echo "Linking..."
    ${sdcc} -o build/snepzhen_solitaire.ihx -mz80 --no-std-crt0 --data-loc 0xC000 ${devkitSMS}/crt0/crt0_sms.rel build/*.rel ${SMSlib}/SMSlib.lib || exit 1

    echo ""
    echo "Generating ROM..."
    ${ihx2sms} build/snepzhen_solitaire.ihx snepzhen_solitaire.sms || exit 1

    echo ""
    echo "Done"
}

# Clean up any old build artefacts
rm -rf build

build_sneptile
build_snepzhen
