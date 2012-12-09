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
 * Render the content received from RQDQL
 */
function render()
{
    // we already rendered it
    if ((render.rendered != undefined) && render.rendered == this.value) {
        return;
    }
    // save it for the future, to avoid double renderings
    render.rendered = this.value;
    rqdql.parse(
        render.rendered,
        function(scope)
        {
            $('#output').html(scope.toString());
        }
    );

    // rqdql.parse(
    //     render.rendered,
    //     function(scope)
    //     {
    //         $('#output')
    //             .empty()
    //             .append('<span/>')
    //                 .find(':last')
    //                 .html(scope.isValid() ? '&#x2714;' : '&#x2718;')
    //                 .css('font-size', '3em')
    //                 .css('color', scope.isValid() ? 'green' : 'red')
    //                 .parent()
    //             .append('<br/>')
    //             .append('<span/>')
    //                 .find(':last')
    //                 .text('RQDQL version:')
    //                 .addClass('header')
    //                 .parent()
    //             .append('<span/>')
    //                 .find(':last')
    //                 .text(scope.getRqdqlVersion())
    //                 .parent()
    //             .append('<br/>')
    //             .append('<span/>')
    //                 .find(':last')
    //                 .text('Ambiguity:')
    //                 .addClass('header')
    //                 .parent()
    //             .append('<span/>')
    //                 .find(':last')
    //                 .text(scope.getAmbiguity())
    //                 .parent()
    //             .append('<br/>')
    //             .append('<span/>')
    //                 .find(':last')
    //                 .text('Errors total:')
    //                 .addClass('header')
    //                 .parent()
    //             .append('<span/>')
    //                 .find(':last')
    //                 .text(scope.getErrorsCount())
    //                 .parent();
    //
    //         // clean the table
    //         $('#lines tbody').empty();
    //         var lines = render.rendered.split("\n");
    //         lines[lines.length] = '';
    //         for (i in lines) {
    //             var line = parseInt(i) + 1;
    //             $('#lines tbody')
    //                 .append('<tr/>')
    //                     .find(':last')
    //                     .append('<td/>')
    //                         .find(':last')
    //                         .text(line.toString())
    //                         .parent()
    //                     .append('<td/>')
    //                         .find(':last')
    //                         .text(lines[i])
    //                         .parent()
    //                     .append('<td/>');
    //
    //             var errors = scope.getErrorsByLine(line);
    //             for (err in errors) {
    //                 $('#lines tbody tr:last td:last')
    //                     .append('<span/>')
    //                     .find(':last')
    //                     .html('&#x24ba;')
    //                     .addClass('marker')
    //                     .attr('title', errors[err]);
    //             }
    //
    //             var objects = scope.getObjectsByLine(line);
    //             for (obj in objects) {
    //                 $('#lines tbody tr:last td:last')
    //                     .append('<span/>')
    //                     .find(':last')
    //                     .addClass('ref')
    //                     .text(objects[obj]);
    //             }
    //         }
    //     }
    // );
};

/**
 * Run this method when the document is loaded
 */
$(document).ready(
    function()
    {
        $("#example").keyup(render);
    }
);
