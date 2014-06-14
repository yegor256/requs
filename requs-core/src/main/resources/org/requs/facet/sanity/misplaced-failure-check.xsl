<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" version="2.0" exclude-result-prefixes="xs">
    <xsl:output method="xml"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="/spec/errors">
        <xsl:copy>
            <xsl:apply-templates select="error"/>
            <xsl:for-each select="//step[position() != last() and signature='fail']">
                <error type="semantic" pos="0">
                    <xsl:attribute name="line">
                        <xsl:value-of select="mentioned/where[position()=1]"/>
                    </xsl:attribute>
                    <xsl:text>Step &quot;</xsl:text>
                    <xsl:value-of select="number"/>
                    <xsl:text>&quot; fails while it is not the last step in the flow</xsl:text>
                </error>
            </xsl:for-each>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>
