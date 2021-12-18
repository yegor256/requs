/**
 * Copyright (c) 2009-2021, Yegor Bugayenko
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 1) Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 * disclaimer. 2) Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 * with the distribution. 3) Neither the name of the requs.org nor
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
package org.requs.facet.syntax.ontology;

/**
 * Slot of a type.
 *
 * @author Yegor Bugayenko (yegor256@gmail.com)
 * @version $Id$
 * @since 1.1
 */
public interface Slot extends Mentioned, Informal {

    /**
     * Arity.
     */
    enum Arity {
        /**
         * One or many.
         */
        MANY("1..*"),
        /**
         * Zero or many: 0..*.
         */
        ANY("0..*"),
        /**
         * Strictly one.
         */
        ONE("1");
        /**
         * Mnemo.
         */
        private final transient String text;
        /**
         * Ctor.
         * @param mnemo Mnemo
         */
        Arity(final String mnemo) {
            this.text = mnemo;
        }
        /**
         * Mnemo.
         * @return Mnemo
         */
        public String mnemo() {
            return this.text;
        }
    }

    /**
     * Assign a type to the slot.
     * @param type Type to assign
     */
    void assign(String type);

    /**
     * Set its arity.
     * @param arity Arity to set
     */
    void arity(Slot.Arity arity);

    /**
     * Is it a composition?
     * @param cmp TRUE if it's a composition
     * @since 1.14
     */
    void composition(boolean cmp);

}
