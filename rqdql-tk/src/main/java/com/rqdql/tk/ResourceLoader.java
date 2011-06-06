/**
 * Copyright (c) 2009-2011, RQDQL.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 1) Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 * disclaimer. 2) Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 * with the distribution. 3) Neither the name of the RQDQL.com nor
 * the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
package com.rqdql.tk;

import java.io.File;
import org.apache.commons.io.FileUtils; // for file manipulation
import org.apache.commons.lang.StringUtils; // for string manipulation
import java.net.URL;
import java.util.ArrayList;

/**
 * @author Yegor Bugayenko (yegor@rqdql.com)
 * @version $Id$
 * @todo #3 Let's move this class to com.ymock:ymock-util package.
 */
public class ResourceLoader {

    /**
     * Find absolute file name of the resource.
     * @param name The name of the resource to find
     * @param The resource found
     */
    public static File find(final String name) {
        return ResourceLoader.locate(
            name,
            Thread.currentThread().getStackTrace()[2]
        );
    }

    /**
     * Load the resource by this name.
     * @param name The name of the resource
     * @return Content of the resource found
     */
    public static String load(final String name) {
        File f = ResourceLoader.locate(
            name,
            Thread.currentThread().getStackTrace()[2]
        );
        try {
            return FileUtils.readFileToString(f);
        } catch (java.io.IOException ex) {
            throw new IllegalArgumentException(ex);
        }
    }

    /**
     * Find absolute file name of the resource.
     * @param name The name of the resource
     * @param element Stack trace element
     * @see #find(String)
     * @see #load(String)
     */
    private static File locate(String name, StackTraceElement element) {
        String dir = "/" + element.getClassName()
            .replace(".", "/")
            .replace("$", "/");
        ArrayList<String> searched = new ArrayList<String>();
        while (dir.contains("/")) {
            URL url = ResourceLoader.class.getResource(dir + "/" + name);
            if (url != null) {
                File f = FileUtils.toFile(url);
                if (f.exists()) {
                    return f;
                }
            }
            searched.add(dir);
            dir = dir.substring(0, dir.lastIndexOf("/"));
        }
        throw new IllegalArgumentException(
            "Resource '" + name + "' not found in any of these paths: "
            + StringUtils.join(searched, ", ")
        );
    }

}
