#!/bin/sh

sdcc="${HOME}/Code/sdcc-4.1.0/bin/sdcc"
devkitSMS="${HOME}/Code/devkitSMS"
SMSlib="${devkitSMS}/SMSlib"
ihx2sms="${devkitSMS}/ihx2sms/Linux/ihx2sms"

mkdir -p build

echo "Compiling..."
for file in main
do
    echo " -> ${file}"
    ${sdcc} -c -mz80 --peep-file ${devkitSMS}/SMSlib/src/peep-rules.txt -I ${SMSlib}/src \
        -o "build/${file}.rel" "source/${file}.c" || exit 1
done

echo "Linking..."
${sdcc} -o build/snepzhen_solitaire.ihx -mz80 --no-std-crt0 --data-loc 0xC000 ${devkitSMS}/crt0/crt0_sms.rel build/*.rel ${SMSlib}/SMSlib.lib || exit 1

echo "Generating ROM..."
${ihx2sms} build/snepzhen_solitaire.ihx snepszhen_solitaire.sms || exit 1

echo "Done"
