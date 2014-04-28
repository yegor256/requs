<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns="http://www.w3.org/1999/xhtml" version="1.0">
    <xsl:include href="_layout.xsl"/>
    <xsl:template name="head">
        <title>NFRs</title>
    </xsl:template>
    <xsl:template name="body">
        <xsl:apply-templates select="/nfrs"/>
    </xsl:template>
    <xsl:template match="nfrs">
        <h1><xsl:text>NFRs</xsl:text></h1>
        <table>
            <thead>
                <tr>
                    <th>ID</th>
                    <th>Method</th>
                    <th>NFR</th>
                    <th>Description</th>
                </tr>
            </thead>
            <tbody>
                <xsl:apply-templates select="nfr"/>
            </tbody>
        </table>
    </xsl:template>
    <xsl:template match="nfr">
        <tr>
            <td><xsl:value-of select="@id"/></td>
            <td><xsl:value-of select="method"/></td>
            <td><xsl:value-of select="name"/></td>
            <td><xsl:value-of select="description"/></td>
        </tr>
    </xsl:template>
</xsl:stylesheet>
