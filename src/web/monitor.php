<?php
$fam_res = fam_open();
$nres = fam_monitor_file( $fam_res, 'log' );

while(1) {
    if ( fam_pending ( $fam_res ) ) $arr = (fam_next_event($fam_res));
}
?>
