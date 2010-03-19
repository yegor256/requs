<?php
/**
 * @version $Id$
 */

$dir = dirname(__FILE__);

$content = file_get_contents('php://stdin');

// log it into file
file_put_contents($dir . '/request.txt', $content);

