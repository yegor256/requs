/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */

def index = new File(basedir, 'target/site/requs.html')
if (!index.exists()) {
    throw new IllegalStateException(
        'Index was not generated at ' + index
    )
}
if (!index.text.contains('SRS')) {
    throw new IllegalStateException(
        'SRS is not in the index ' + index
    )
}

def dir = new File(basedir, 'target/site/requs')
if (!dir.exists()) {
    throw new IllegalStateException(
        'Report was not generated at ' + dir
    )
}
if (!dir.isDirectory()) {
    throw new IllegalStateException(
        'Report is not a directory: ' + dir
    )
}
