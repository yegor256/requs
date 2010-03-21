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

// log there all our operations
global $log;
$log = fopen($dir . '/response.txt', 'w');

function nice($str)
{
    return "'" . wordwrap(substr(str_replace("\n", '\\n', $str), 0, 400), 100, "\n\t") . "...' (" .
    strlen($str) . ' bytes)';
}

function logg($message)
{
    global $log;
    fprintf($log, $message);
}

logg(
    "HOOK REVISION: {$revision}\n" .
    "TIME: " . date('d/m/y h:i:s') . "\n" .
    "CLI: {$rqdql}\n"
);

// start collecting all error messages
ob_start();

try {
    $lines = explode("\n", $content);
    $comment = $lines[0];
    
    logg(
        "CONTENT:" . nice($content) . "\n" .
        "COMMENT: " . nice($comment) . "\n"
    );
        
    // empty comment shall be disallowed. every comment
    // shall contain a link to the ticket, which motivated the change
    // we don't EXIT here, since the output sent will notify
    // Trac that there are some errors and the page won't be saved
    if (!preg_match('/#\d+/', $comment)) {
        throw new Exception('comment: your comment shall contain a link to a motivating ticket');
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
                throw new Exception();
            }
        } else {
            $scopePages[$name] = $lines;
            if (is_null($thisPage)) {
                $thisPage = $name;
            }
        }
    }

    logg(
        "THIS PAGE NAME: {$thisPage} (" . count($scopePages[$thisPage]) . " lines)\n" .
        "PAGES TOTAL: " . count($pages) . "\n" .
        "SCOPE PAGES TOTAL: " . count($scopePages) . "\n"
    );

    // group all lines into one single stream
    $stream = array();
    foreach ($scopePages as $page) {
        foreach ($page as $lns) {
            $stream[] = $lns;
        }
    }

    logg(
        'TO RQDQL: ' . nice(implode(' ', $stream)) . "\n"
    );

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
    if (!is_resource($proc)) {
        throw new Exception('failed to start RQDQL');
    }
    fwrite($pipes[0], implode("\n", $stream));
    fclose($pipes[0]);
    $out = stream_get_contents($pipes[1]);
    fclose($pipes[1]);
    $result = proc_close($proc);

    logg(
        'STREAM: ' . nice(implode(' ', $stream)) . "\n" .
        'STREAM LINES: ' . count($stream) . "\n" . 
        "RETURN: {$result}\n" .
        'RQDQL OUT: '  . nice($out) . "\n"
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
    
    logg(
        "DEFECTIVE LINES: " . implode(', ', array_keys($messages)) . "\n"
    );

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
} catch (Exception $e) {
    if ($e->getMessage()) {
        echo "{$e->getMessage()}\n";
    }
}    

// get all lines outputed above
$output = ob_get_clean();

logg(
    'MESSAGE TO TRAC: ' . nice($output)
);

fclose($log);

if ($output) {
    echo "RqdqlPlugin: rev{$revision}\n";
    echo $output;
    exit(-1);
} else {
    // everything is OK!
    exit(0);
}