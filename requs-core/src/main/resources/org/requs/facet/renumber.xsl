<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:r="org.requs" exclude-result-prefixes="r"
    version="2.0">
    <xsl:output method="xml" cdata-section-elements="svg html"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="mentioned/where">
        <xsl:variable name="line" select="number(.)"/>
        <xsl:copy>
            <xsl:value-of select="r:file(/spec/files, $line)"/>
            <xsl:text>:</xsl:text>
            <xsl:value-of select="r:line(/spec/files, $line)"/>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="error">
        <xsl:variable name="line" select="number(@line)"/>
        <xsl:copy>
            <xsl:attribute name="file">
                <xsl:value-of select="r:file(/spec/files, $line)"/>
            </xsl:attribute>
            <xsl:attribute name="line">
                <xsl:value-of select="r:line(/spec/files, $line)"/>
            </xsl:attribute>
            <xsl:apply-templates select="node()|(@* except @line)"/>
        </xsl:copy>
    </xsl:template>
    <xsl:function name="r:file">
        <xsl:param name="files"/>
        <xsl:param name="line"/>
        <xsl:value-of select="$files/file[@line &lt;= $line and not(following-sibling::file/@line &lt;= $line)]/@id"/>
    </xsl:function>
    <xsl:function name="r:line">
        <xsl:param name="files"/>
        <xsl:param name="line"/>
        <xsl:value-of select="$line - $files/file[@id=r:file($files, $line)]/@line + 1"/>
    </xsl:function>
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>
