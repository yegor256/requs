<?php
/**
 * @version $Id$
 */

$dir = dirname(__FILE__);
$rqdql = $dir . '/rqdql';

$content = file_get_contents('php://stdin');

$lines = explode("\n", $content);
$comment = $lines[0];

$pages = array();

for ($i=1; $i<count($lines); $i++) {
    $name = $lines[$i];
    $linesNo = intval($lines[$i+1]);
    $pages[$lines[$i]] = array_slice($lines, $i+2, $linesNo);
    $i += 2 + $linesNo;
}

foreach ($pages as $name=>&$lines) {
    $outOfScope = true;
    foreach ($lines as &$line) {
        if (preg_match('/^\s*=\s+SRS:.*?=$\s*/', $line)) {
            $outOfScope = false;
        }
        $replacers = array(
            '/^\s+\*(.*)$/' => '${1}', // skip spaces before LIST ITEMS
            '/^\s*(.*)\s*$/' => '${1}', // remove leading and trailing spaces
            '/^\s*=+\s+.*?\s+=+\s*$/' => '', // kill headers
            '/\[\[.*?\]\]/' => '', // kill meta-includers of Trac
        );
        $line = preg_replace(
            array_keys($replacers),
            $replacers,
            $line
        );
    }
    if ($outOfScope) {
        unset($pages[$name]);
    }
}

$stream = array();
foreach ($pages as $page) {
    foreach ($page as $lns) {
        $stream[] = $lns;
    }
}
$thisPage = array_shift($pages);

$proc = proc_open(
    $rqdql,
    array(
        0 => array('pipe', 'r'),
        1 => array('pipe', 'w'),
        2 => array('pipe', 'w'),
    ),
    $pipes
);
fwrite($pipes[0], implode("\n", $stream));
fclose($pipes[0]);
$out = stream_get_contents($pipes[1]);
$result = proc_close($proc);

$errors = explode("\n", $out);
$messages = array();
foreach ($errors as $error) {
    $matches = array();
    if (preg_match('/^\[(?:ERR|WARN)\]\s(\d+)\.(\d+)\s(.*)$/', $error, $matches)) {
        $lineNo = intval($matches[1]);
        if ($lineNo > count($thisPage)) {
            break;
        }
        if (!isset($messages[$lineNo])) {
            $messages[$lineNo] = '';
        }
        $messages[$lineNo] .= ($messages[$lineNo] ? '; ' : false) . $matches[3];
    }
}

foreach ($messages as $lineNo=>$message) {
    echo sprintf(
        "line %d (%s): %s\n",
        $lineNo,
        $stream[$lineNo-1],
        $message
    );
}
exit(-1);
