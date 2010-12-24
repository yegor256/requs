/**
 * RQDQL.com
 *
 * This source file is subject to the new BSD license that is bundled
 * with this package in the file LICENSE.txt. It is also available
 * through the world-wide-web at this URL: http://www.rqdql.com/LICENSE.txt
 * If you did not receive a copy of the license and are unable to
 * obtain it through the world-wide-web, please send an email
 * to license@rqdql.com so we can send you a copy immediately.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 */
package com.rqdql.api;

// for management of listeners
import java.util.ArrayList;
import java.util.List;

/**
 * Auditor that accepts {@link Notion}s and passes them
 * to other listeners.
 *
 * <p>It is a signleton pattern, meaning that you can't instantiate
 * the class explicitly, but should always get an access to its
 * instance via {@link @getInstance()} method.
 *
 * @author Yegor Bugayenko (yegor@rqdql.com)
 * @version $Id$
 */
public final class Auditor {

    /**
     * A unique instance of this class.
     */
    private static Auditor instance;

    /**
     * List of listeners.
     */
    private List<NotionListener> listeners;

    /**
     * Private ctor, to avoid direct instantiation of the class.
     */
    private Auditor() {
        this.listeners = new ArrayList<NotionListener>();
    }

    /**
     * Get an instance of this class.
     *
     * @return The auditor to use
     */
    public Auditor getInstance() {
        if (Auditor.instance == null) {
            Auditor.instance = new Auditor();
        }
        return Auditor.instance;
    }

    /**
     * Add new listener of {@link Notion}-s.
     *
     * @param listener The {@link NotionListener}
     */
    public void addListener(final NotionListener listener) {
        this.listeners.add(listener);
    }

    /**
     * Inform auditor about a new {@link Notion}.
     *
     * @param notion A piece of new information
     */
    public void tell(final Notion notion) {
        for (NotionListener listener : this.listeners) {
            listener.listenNotion(notion);
        }
    }

}
