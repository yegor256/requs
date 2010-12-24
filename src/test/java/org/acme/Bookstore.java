/**
 * @version $Id$
 */
package org.acme;

// for logging
import com.rqdql.Log;

/**
 * Store of books.
 */
public class Bookstore {

    /**
     * Logs a simple line
     */
    public static void ping(final String msg) {
        Log.info(msg);
    }

}

