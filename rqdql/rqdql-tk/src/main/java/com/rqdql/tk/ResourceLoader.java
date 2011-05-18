/**
 * @version $Id$
 */
package com.rqdql.tk;

import java.io.File;
import org.apache.commons.io.FileUtils; // for file manipulation
import org.apache.commons.lang.StringUtils; // for string manipulation
import java.net.URL;
import java.util.ArrayList;

public class ResourceLoader {

    /**
     * Find absolute file name of the resource.
     */
    public static File find(final String name) {
        return ResourceLoader.locate(name, Thread.currentThread().getStackTrace()[2]);
    }

    /**
     * Load the resource by this name.
     */
    public static String load(final String name) {
        File f = ResourceLoader.locate(name, Thread.currentThread().getStackTrace()[2]);
        try {
            return FileUtils.readFileToString(f);
        } catch (java.io.IOException ex) {
            throw new RuntimeException(ex);
        }
    }

    /**
     * Find absolute file name of the resource.
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
        throw new RuntimeException(
            "Resource '" + name + "' not found in any of these paths: "
            + StringUtils.join(searched, ", ")
        );
    }

}
