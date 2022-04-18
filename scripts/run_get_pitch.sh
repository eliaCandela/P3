#!/bin/bash

# Put here the program (maybe with path)
GETF0="get_pitch --umaxnorm=0.40 --u1norm=0.96 --upot=33.0"

for fwav in pitch_db/train/*.wav; do
    ff0=${fwav/.wav/.f0}
    echo "$GETF0 $fwav $ff0 ----"
    $GETF0 $fwav $ff0 > /dev/null || (echo "Error in $GETF0 $fwav $ff0"; exit 1)
done

exit 0
