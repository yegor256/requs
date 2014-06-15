<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" version="2.0" exclude-result-prefixes="xs">
    <xsl:output method="xml" cdata-section-elements="svg html"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="/spec/errors">
        <xsl:copy>
            <xsl:apply-templates select="error"/>
            <xsl:for-each select="/spec/types/type/slots/slot[type]">
                <xsl:variable name="slot" select="."/>
                <xsl:if test="/spec[not(types/type/name=$slot/type)]">
                    <error type="seal" pos="0">
                        <xsl:attribute name="line">
                            <xsl:value-of select="$slot/mentioned/where[position()=1]"/>
                        </xsl:attribute>
                        <xsl:text>Slot &quot;</xsl:text>
                        <xsl:value-of select="$slot/name"/>
                        <xsl:text>&quot; of type &quot;</xsl:text>
                        <xsl:value-of select="$slot/../../name"/>
                        <xsl:text>&quot; refers to a non-existing type &quot;</xsl:text>
                        <xsl:value-of select="$slot/type"/>
                        <xsl:text>&quot;</xsl:text>
                    </error>
                </xsl:if>
            </xsl:for-each>
            <xsl:for-each select="/spec/methods/method/bindings/binding">
                <xsl:variable name="binding" select="."/>
                <xsl:if test="/spec/types[not(type/name=$binding/type)]">
                    <error type="seal" pos="0">
                        <xsl:attribute name="line">
                            <xsl:value-of select="$binding/../../mentioned/where[position()=1]"/>
                        </xsl:attribute>
                        <xsl:text>Use case &quot;</xsl:text>
                        <xsl:value-of select="$binding/../../id"/>
                        <xsl:text>&quot; refers to a non-existing type &quot;</xsl:text>
                        <xsl:value-of select="$binding/type"/>
                        <xsl:text>&quot;</xsl:text>
                    </error>
                </xsl:if>
            </xsl:for-each>
            <xsl:for-each select="/spec/types/type/parents/type">
                <xsl:variable name="type" select="."/>
                <xsl:if test="/spec[not(types/type/name=$type)]">
                    <error type="seal" pos="0">
                        <xsl:attribute name="line">
                            <xsl:value-of select="$type/../../mentioned/where[position()=1]"/>
                        </xsl:attribute>
                        <xsl:text>Parent of type &quot;</xsl:text>
                        <xsl:value-of select="$type/../../name"/>
                        <xsl:text>&quot; refers to a non-existing type &quot;</xsl:text>
                        <xsl:value-of select="$type"/>
                        <xsl:text>&quot;</xsl:text>
                    </error>
                </xsl:if>
            </xsl:for-each>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>
