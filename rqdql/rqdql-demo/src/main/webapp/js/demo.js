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
 *
 * @author Yegor Bugayenko <egor@rqdql.com>
 * @copyright Copyright (c) rqdql.com, 2010-2012
 * @version $Id$
 */

/**
 * Run this method when the document is loaded
 */
$(document).ready(
    function() {
        $("#example").keyup(
            function() {
                if ((this.rendered != undefined) && this.rendered == this.value) {
                    return;
                }
                this.rendered = this.value;
                if (this.rendered == null) {
                    this.rendered = "";
                }
                $.ajax(
                    {
                        url: "/instant",
                        data: { 'text': this.rendered },
                        type: 'POST',
                        dataType: 'text',
                        success: function(data)
                        {
                            $('#output').text(data);
                        },
                        error: function(XMLHttpRequest, textStatus, errorThrown)
                        {
                            $('#output').html(textStatus);
                        }
                    }
                );
            }
        );
    }
);
