<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:fn="http://www.w3.org/2005/xpath-functions"
    xmlns:r="org.requs.facet.XsltFuncs"
    version="2.0" exclude-result-prefixes="xs fn r">
    <xsl:output method="xml"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="/spec">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="method">
        <xsl:variable name="md">
            <x>
                <xsl:apply-templates select="." mode="x"/>
            </x>
        </xsl:variable>
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
            <markdown>
                <xsl:value-of select="r:print($md)"/>
            </markdown>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="method" mode="x">
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
                                <xsl:apply-templates select="." mode="x"/>
                            </xsl:for-each>
                        </td>
                    </tr>
                </xsl:if>
                <xsl:if test="steps/step">
                    <tr>
                        <td><xsl:text>Success Flow</xsl:text></td>
                        <td>
                            <xsl:apply-templates select="steps" mode="x"/>
                        </td>
                    </tr>
                </xsl:if>
                <xsl:if test="nfrs/nfr">
                    <tr>
                        <td><xsl:text>NFRs</xsl:text></td>
                        <td>
                            <xsl:apply-templates select="nfrs" mode="x"/>
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
                            <xsl:apply-templates select="/spec/types/type[name=current()/type]" mode="x"/>
                        </td>
                    </tr>
                </xsl:for-each>
            </tbody>
        </table>
    </xsl:template>
    <xsl:template match="steps" mode="x">
        <xsl:for-each select="step">
            <xsl:if test="position() != 1">
                <br/>
            </xsl:if>
            <xsl:apply-templates select="." mode="x"/>
        </xsl:for-each>
    </xsl:template>
    <xsl:template match="step" mode="x">
        <xsl:value-of select="number"/>
        <xsl:text>. </xsl:text>
        <xsl:call-template name="signature">
            <xsl:with-param name="home" select="."/>
        </xsl:call-template>
    </xsl:template>
    <xsl:template match="informal" mode="x">
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
    <xsl:template match="type" mode="x">
        <xsl:for-each select="info/informal">
            <xsl:if test="position() > 1">
                <br/>
            </xsl:if>
            <xsl:apply-templates select="." mode="x"/>
        </xsl:for-each>
        <xsl:if test="slots/slot">
            <ul>
                <xsl:for-each select="slots/slot">
                    <li>
                        <code><xsl:value-of select="name"/></code>
                        <xsl:text>: </xsl:text>
                        <xsl:value-of select="type"/>
                        <xsl:apply-templates select="info" mode="x"/>
                    </li>
                </xsl:for-each>
            </ul>
        </xsl:if>
    </xsl:template>
    <xsl:template match="nfrs">
        <xsl:for-each select="nfr">
            <xsl:if test="position() != 1">
                <br/>
            </xsl:if>
            <xsl:apply-templates select="." mode="x"/>
        </xsl:for-each>
    </xsl:template>
    <xsl:template match="nfr">
        <xsl:value-of select="id"/>
        <xsl:text> must </xsl:text>
        <xsl:apply-templates select="info" mode="x"/>
    </xsl:template>
    <xsl:template match="info" mode="x">
        <xsl:if test="informal">
            <xsl:text> </xsl:text>
            <xsl:for-each select="informal">
                <xsl:if test="position() > 1">
                    <xsl:text> and </xsl:text>
                </xsl:if>
                <xsl:apply-templates select="." mode="x"/>
            </xsl:for-each>
        </xsl:if>
    </xsl:template>
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>
