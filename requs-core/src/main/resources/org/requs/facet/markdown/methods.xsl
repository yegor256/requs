<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:fn="http://www.w3.org/2005/xpath-functions"
    version="2.0" exclude-result-prefixes="xs fn">
    <xsl:output method="xml"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="/">
        <pages>
            <methods>
                <xsl:apply-templates select="spec/methods/method"/>
            </methods>
        </pages>
    </xsl:template>
    <xsl:template match="method">
        <xsl:copy>
            <id><xsl:value-of select="id"/></id>
            <text>
                <xsl:text>The following table describes all technical details of Use Case `</xsl:text>
                <xsl:value-of select="id"/>
                <xsl:text>`:&#10;&#10;</xsl:text>
                <table>
                    <thead>
                        <tr>
                            <th><xsl:text>Property</xsl:text></th>
                            <th><xsl:text>Details</xsl:text></th>
                        </tr>
                    </thead>
                    <tbody>
                        <tr>
                            <td><xsl:text>ID</xsl:text></td>
                            <td><xsl:value-of select="id"/></td>
                        </tr>
                        <tr>
                            <td><xsl:text>Signature</xsl:text></td>
                            <td>
                                <xsl:call-template name="signature">
                                    <xsl:with-param name="home" select="."/>
                                </xsl:call-template>
                            </td>
                        </tr>
                        <tr>
                            <td><xsl:text>Primary</xsl:text></td>
                            <td><xsl:value-of select="bindings/binding[name='_self']/type"/></td>
                        </tr>
                        <tr>
                            <td><xsl:text>Actors</xsl:text></td>
                            <td>
                                <xsl:for-each select="bindings/binding[name!='_self']">
                                    <xsl:if test="position() != 1">
                                        <xsl:text>; </xsl:text>
                                    </xsl:if>
                                    <code><xsl:value-of select="name"/></code>
                                    <xsl:text> as </xsl:text>
                                    <xsl:value-of select="type"/>
                                </xsl:for-each>
                            </td>
                        </tr>
                        <xsl:if test="info/informal">
                            <tr>
                                <td><xsl:text>Brief</xsl:text></td>
                                <td>
                                    <xsl:for-each select="info/informal">
                                        <xsl:if test="position() != 1">
                                            <br/>
                                        </xsl:if>
                                        <xsl:apply-templates select="."/>
                                    </xsl:for-each>
                                </td>
                            </tr>
                        </xsl:if>
                        <xsl:if test="steps/step">
                            <tr>
                                <td><xsl:text>Success Flow</xsl:text></td>
                                <td>
                                    <xsl:apply-templates select="steps"/>
                                </td>
                            </tr>
                        </xsl:if>
                    </tbody>
                </table>
                <xsl:text>&#10;&#10;Actors taking participation in the Use Case have the following properties:&#10;&#10;</xsl:text>
                <table>
                    <thead>
                        <tr>
                            <th><xsl:text>Actor</xsl:text></th>
                            <th><xsl:text>Properties</xsl:text></th>
                        </tr>
                    </thead>
                    <tbody>
                        <xsl:for-each select="bindings/binding">
                            <tr>
                                <td>
                                    <xsl:value-of select="type"/>
                                </td>
                                <td>
                                    <xsl:apply-templates select="/spec/types/type[name=current()/type]"/>
                                </td>
                            </tr>
                        </xsl:for-each>
                    </tbody>
                </table>
            </text>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="steps">
        <xsl:for-each select="step">
            <xsl:if test="position() != 1">
                <br/>
            </xsl:if>
            <xsl:apply-templates select="."/>
        </xsl:for-each>
    </xsl:template>
    <xsl:template match="step">
        <xsl:value-of select="number"/>
        <xsl:text>. </xsl:text>
        <xsl:call-template name="signature">
            <xsl:with-param name="home" select="."/>
        </xsl:call-template>
    </xsl:template>
    <xsl:template match="informal">
        <xsl:text>&quot;</xsl:text>
        <xsl:value-of select="fn:replace(., '[&#10; ]+', ' ')"/>
        <xsl:text>&quot;</xsl:text>
    </xsl:template>
    <xsl:template name="signature">
        <xsl:param name="home" />
        <code><xsl:value-of select="$home/object"/></code>
        <xsl:text> </xsl:text>
        <xsl:value-of select="$home/signature"/>
        <xsl:if test="$home/result">
            <xsl:text> </xsl:text>
            <code><xsl:value-of select="$home/result"/></code>
        </xsl:if>
        <xsl:if test="$home/args/arg">
            <xsl:text> using </xsl:text>
            <xsl:for-each select="$home/args/arg">
                <xsl:if test="position() > 1">
                    <xsl:text> and </xsl:text>
                </xsl:if>
                <code><xsl:value-of select="."/></code>
            </xsl:for-each>
        </xsl:if>
    </xsl:template>
    <xsl:template match="type">
        <xsl:for-each select="info/informal">
            <xsl:if test="position() > 1">
                <br/>
            </xsl:if>
            <xsl:apply-templates select="."/>
        </xsl:for-each>
        <xsl:if test="slots/slot">
            <ul>
                <xsl:for-each select="slots/slot">
                    <li>
                        <code><xsl:value-of select="name"/></code>
                        <xsl:text>: </xsl:text>
                        <xsl:value-of select="type"/>
                        <xsl:if test="info/informal">
                            <xsl:text> </xsl:text>
                            <xsl:for-each select="info/informal">
                                <xsl:if test="position() > 1">
                                    <xsl:text> and </xsl:text>
                                </xsl:if>
                                <xsl:apply-templates select="."/>
                            </xsl:for-each>
                        </xsl:if>
                    </li>
                </xsl:for-each>
            </ul>
        </xsl:if>
    </xsl:template>
</xsl:stylesheet>
