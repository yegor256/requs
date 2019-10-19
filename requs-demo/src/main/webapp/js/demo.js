/**
 * requs.org
 *
 * This source file is subject to the new BSD license that is bundled
 * with this package in the file LICENSE.txt. It is also available
 * through the world-wide-web at this URL: http://www.requs.org/LICENSE.txt
 * If you did not receive a copy of the license and are unable to
 * obtain it through the world-wide-web, please send an email
 * to license@requs.org so we can send you a copy immediately.
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
 * @author Yegor Bugayenko <egor@tpc2.com>
 * @copyright Copyright (c) requs.org, 2010-2017
 * @version $Id$
 */

/*globals $: false, document: false */

function post(html) {
  'use strict';
  var iframe = document.getElementById('srs'),
    doc = iframe.contentWindow.document;
  iframe.doctype = 'xhtml';
  doc.open();
  doc.write(html);
  doc.close();
}

/**
 * Run this method when the document is loaded
 */
$(document).ready(
  function () {
    'use strict';
    $('.separator').click(
      function () {
        $('#annex').toggle();
      }
    );
    $('#example').keyup(
      function () {
        if (this.busy) {
          return;
        }
        if ((this.rendered !== undefined) && this.rendered === this.value) {
          return;
        }
        this.rendered = this.value;
        if (this.rendered === null) {
          this.rendered = '';
        }
        var fn = this, $output = $('#output'), $sep = $('#sep');
        fn.busy = true;
        $.ajax(
          {
            url: '/instant',
            data: { 'text': this.rendered },
            type: 'POST',
            dataType: 'json',
            beforeSend: function () {
              $sep.css('color', 'red');
              $sep.text('loading...');
            },
            success: function (data) {
              $output.text(data.spec);
              $sep.text(data.spec.length + ' bytes in XML');
              $output.css('color', 'inherit');
              post(data.html);
            },
            error: function (xhr) {
              $output.text(xhr.responseText);
              $output.css('color', 'red');
              post(
                [
                  '<html><body><span style="color:red">Internal application error</span>.',
                  ' Please submit your sources as',
                  ' <a href="https://github.com/yegor256/requs">a Github issue</a>',
                  '</body></html>'
                ].join('')
              );
            },
            complete: function () {
              $sep.css('color', 'inherit');
              fn.busy = false;
            }
          }
        );
      }
    ).keyup();
  }
);
