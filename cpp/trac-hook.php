<?php
/**
 * @version $Id$
 */

// the content of this string is changed by SVN because
// of svn:keywords properties. don't try to change it manually
// it is changed with every SVN UP command.
$revision = intval(substr('$Rev$', 6));

$dir = dirname(__FILE__);
$rqdql = $dir . '/rqdql';

$content = file_get_contents('php://stdin');
// just to log it
file_put_contents($dir . '/request.txt', $content);

// start collecting all error messages
ob_start();

$lines = explode("\n", $content);
$comment = $lines[0];

// empty comment shall be disallowed. every comment
// shall contain a link to the ticket, which motivated the change
// we don't EXIT here, since the output sent will notify
// Trac that there are some errors and the page won't be saved
if (!preg_match('/#\d+/', $comment)) {
    echo "comment: your comment shall contain a link to a motivating ticket\n";
}

// split input buffer into pages and lines
$pages = array();
for ($i=1; $i<count($lines); $i++) {
    $name = $lines[$i];
    $linesNo = intval($lines[$i+1]);
    $pages[$lines[$i]] = array_slice($lines, $i+2, $linesNo);
    $i += 2 + $linesNo;
}

// filter-out lines/pages which are not related to scope
$scopePages = array();
$thisPage = null;
foreach ($pages as $name=>$lines) {
    $outOfScope = true;
    foreach ($lines as &$line) {
        if (preg_match('/^\s*=\s+SRS:.*?\s+=\s*$/s', $line)) {
            $outOfScope = false;
        }
        $replacers = array(
            '/^\s+\*(.*)$/'         => '${1}', // skip spaces before LIST ITEMS
            '/^\s+\d+\.(.*)$/'      => '${1}', // skip spaces before ENUMERATE ITEMS
            '/^\s*(.*)\s*$/'        => '${1}', // remove leading and trailing spaces
            '/^\s*=+\s+.*?\s+=+\s*$/' => '', // kill headers
            '/\[\[.*?\]\]/'         => '', // kill meta-includers of Trac
            '/\[wiki:(.*?)\]/'      => '${1}', // convert wiki names to string
            '/\[.*?\s(.*?)\]/'      => '${1}', // convert wiki links to strings
            '/\[(.*?)\]/'           => '${1}', // convert wiki links to strings
            '/\'{2,3}(.*?)\'{2,3}/' => '${1}', // convert bold and italic to normal text
        );
        $line = preg_replace(
            array_keys($replacers),
            $replacers,
            $line
        );
    }
    if ($outOfScope) {
        if (is_null($thisPage)) {
            $thisPage = false;
        }
    } else {
        $scopePages[$name] = $lines;
        if (is_null($thisPage)) {
            $thisPage = $name;
        }
    }
}

if ($thisPage) {
    // group all lines into one single stream
    $stream = array();
    foreach ($scopePages as $page) {
        foreach ($page as $lns) {
            $stream[] = $lns;
        }
    }

    // execute RQDQL
    $pipes = array();
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
    // just to log it
    file_put_contents(
        $dir . '/response.txt',
        "CLI: {$rqdql}\n" .
        "PAGES TOTAL: " . count($pages) . "\n" .
        "SCOPE PAGES TOTAL: " . count($scopePages) . "\n" .
        "STDIN: " . substr(implode(' ', $stream), 0, 200) . "...\n" .
        "RETURN: {$result}\n" .
        'OUT (' . strlen($out) . "):\n{$out}"
    );

    // convert all errors found in RQDQL into defects for Trac
    $errors = explode("\n", $out);
    $messages = array();
    foreach ($errors as $error) {
        $matches = array();
        if (preg_match('/^\[(?:ERR|WARN)\]\s(\d+)\.(\d+)\s(.*)$/', $error, $matches)) {
            $lineNo = intval($matches[1]);
            if ($lineNo > count($scopePages[$thisPage])) {
                break;
            }
            if (!isset($messages[$lineNo])) {
                $messages[$lineNo] = '';
            }
            $messages[$lineNo] .= ($messages[$lineNo] ? '; ' : false) . $matches[3];
        }
    }

    // convert all found messages into Trac-friendly 
    // notifications (FIELD:MESSAGE)
    foreach ($messages as $lineNo=>$message) {
        echo sprintf(
            "line %d: (%s) %s\n",
            $lineNo,
            $stream[$lineNo-1],
            $message
        );
    }
}

// get all lines outputed above
$output = ob_get_clean();
if ($output) {
    echo "RqdqlPlugin: rev{$revision}\n";
    echo $output;
} else {
    // everything is OK!
    exit(0);
}